// Copyright Mostafa Ibrahem


#include "Player/FrozenPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Input/FrozenInputComponent.h"
#include "Interaction/EnemyInterface.h"

AFrozenPlayerController::AFrozenPlayerController()
{
	bReplicates = true;
}

void AFrozenPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	
	CursorTrace();
	
	
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
	
	
	FrozenInputComponent->BindAbilityActions(FrozenInputConfig,this,&AFrozenPlayerController::AbilityInputTagPressed,&AFrozenPlayerController::AbilityInputTagReleased,
		&AFrozenPlayerController::AbilityInputTagHeld);
	
	

}
void AFrozenPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(1,3,FColor::Blue ,*InputTag.ToString());
}

void AFrozenPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(2,3,FColor::Red ,*InputTag.ToString());
}

void AFrozenPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(3,3,FColor::Green ,*InputTag.ToString());
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
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
	if (!CursorHit.bBlockingHit)return;
	
	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();
	if (LastActor ==nullptr)
	{
		if (ThisActor != nullptr)
		{
			ThisActor->HighlightActor();
			
		}
	}
	else
	{
		if (ThisActor == nullptr)
		{
			 LastActor->UnHighlightActor();
			
		}
		else
		{
			if (LastActor != ThisActor)
			{
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
		}
	}
		
}

