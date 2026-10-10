// Copyright Mostafa Ibrahem


#include "Player/FrozenPlayerState.h"
#include "AbilitySystem/FrozenAbilitySystemComponent.h"
#include "AbilitySystem/FrozenAttributeSet.h"
#include "Net/UnrealNetwork.h"


AFrozenPlayerState::AFrozenPlayerState()
{
	NetUpdateFrequency = 100.f;
	AbilitySystemComponent = CreateDefaultSubobject<UFrozenAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UFrozenAttributeSet>("AttributeSet");
}

void AFrozenPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AFrozenPlayerState,Level)
	
	
	
	
}

UAbilitySystemComponent* AFrozenPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AFrozenPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}

void AFrozenPlayerState::OnRep_Level(int32 OldLevel)
{
	
}
