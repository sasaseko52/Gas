// Copyright Mostafa Ibrahem


#include "Player/FrozenPlayerController.h"
#include "EnhancedInputSubsystems.h"

AFrozenPlayerController::AFrozenPlayerController()
{
	bReplicates = true;
}

void AFrozenPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(FrozenContext);
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(FrozenContext,0);
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}
