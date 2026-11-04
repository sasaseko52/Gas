// Copyright Mostafa Ibrahem


#include "Player/FrozenPlayerController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "FrozenGameplayTags.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/FrozenAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Input/FrozenInputComponent.h"
#include "Interaction/EnemyInterface.h"

AFrozenPlayerController::AFrozenPlayerController()
{
	bReplicates = true;
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}


void AFrozenPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	
	CursorTrace();
	
	AutoRun();
	
}
void AFrozenPlayerController::AutoRun()
{
	if (!bAutoRunning) return;
	if (APawn* ControllerPawn = GetPawn())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControllerPawn->GetActorLocation(),ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline,ESplineCoordinateSpace::World); 
		ControllerPawn->AddMovementInput(Direction);
		
		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}

void AFrozenPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(FrozenContext);
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(FrozenContext,0);
	}
		
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AFrozenPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UFrozenInputComponent* FrozenInputComponent = CastChecked<UFrozenInputComponent>(InputComponent);
	
	FrozenInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AFrozenPlayerController::Move);
	
	FrozenInputComponent->BindAction(ShiftAction,ETriggerEvent::Started,this,&AFrozenPlayerController::ShiftPressed);
	FrozenInputComponent->BindAction(ShiftAction,ETriggerEvent::Completed,this,&AFrozenPlayerController::ShiftReleased);
	
	FrozenInputComponent->BindAbilityActions(FrozenInputConfig,this,&AFrozenPlayerController::AbilityInputTagPressed,&AFrozenPlayerController::AbilityInputTagReleased,
		&AFrozenPlayerController::AbilityInputTagHeld);
	
	

}
void AFrozenPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	//Check if the pressed Button is the LMB
	if (InputTag.MatchesTagExact(FFrozenGameplayTags::Get().InputTag_LMB))
	{
		bTargeting =  ThisActor  ? true : false;
		bAutoRunning = false;
	}
	
}

void AFrozenPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	//Check if the Released Button is not the LMB  just  Activate the Ability Assigned to that tag DIRECTLY
	if (!InputTag.MatchesTagExact(FFrozenGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagReleased(InputTag);
		}
		return;
	}
	if (GetASC())
	{
		GetASC()->AbilityInputTagReleased(InputTag);
	}
	if (!bTargeting && !bShiftPressed )
	{
		APawn* ControllerPawn = GetPawn();
		if (FollowTime <= ShortPressThreshold && ControllerPawn)
		{
			
			if (UNavigationPath* NavigationPath = UNavigationSystemV1::FindPathToLocationSynchronously(this , ControllerPawn->GetActorLocation(),CachedDestination))
			{
				Spline->ClearSplinePoints();
				for (const FVector& Point : NavigationPath->PathPoints)
				{
					Spline->AddSplinePoint(Point,ESplineCoordinateSpace::World);
					
				}
				CachedDestination = NavigationPath->PathPoints[NavigationPath->PathPoints.Num()-1];
				bAutoRunning = true;
			}
			
		}
		FollowTime = 0;
		bTargeting = false;
	}
	
}

void AFrozenPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	//Check if the pressed Button is not the LMB just  Activate the Ability Assigned to that tag DIRECTLY
	if (!InputTag.MatchesTagExact(FFrozenGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
		
		return;
	}
	
	if (bTargeting  || bShiftPressed)
	{
		// Activate Ability 
		
		if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
		
	}
	else
	{
		//Click  to MOVE
		FollowTime += GetWorld()->GetDeltaSeconds();
		
		if (CursorHit.bBlockingHit)
		{
			CachedDestination = CursorHit.ImpactPoint;
		}
		
		if (APawn* ControllerPawn = GetPawn())
		{
			FVector WorldDirection = (CachedDestination - ControllerPawn->GetActorLocation()).GetSafeNormal();
			ControllerPawn->AddMovementInput(WorldDirection);
		}
	}
	
}

UFrozenAbilitySystemComponent* AFrozenPlayerController::GetASC() 
{
	if (FrozenAbilitySystemComponent == nullptr)

	{
		FrozenAbilitySystemComponent = Cast<UFrozenAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()));
	}
	return FrozenAbilitySystemComponent;
}

void AFrozenPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation  (0.f ,Rotation.Yaw,0.f);
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection,InputAxisVector.X);
	}
}

void AFrozenPlayerController::CursorTrace()
{
	
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
	if (!CursorHit.bBlockingHit)return;
	
	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();
	
	if (LastActor != ThisActor)
	{
		if (LastActor) LastActor->UnHighlightActor();
		if (ThisActor) ThisActor->HighlightActor();
	}
}

