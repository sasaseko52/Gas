// Copyright Mostafa Ibrahem


#include "Character/PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/FrozenPlayerState.h"

APlayerCharacter::APlayerCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f,400.f,0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
}


void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfo(); 
}

void APlayerCharacter::InitAbilityActorInfo()
{
	AFrozenPlayerState* FrozenPlayerState = GetPlayerState<AFrozenPlayerState>();
	check(FrozenPlayerState);
	FrozenPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(FrozenPlayerState,this);
	AbilitySystemComponent = FrozenPlayerState->GetAbilitySystemComponent();
	AttributeSet = FrozenPlayerState->GetAttributeSet();
}
