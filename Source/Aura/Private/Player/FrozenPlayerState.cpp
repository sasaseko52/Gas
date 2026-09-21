// Copyright Mostafa Ibrahem


#include "Player/FrozenPlayerState.h"

#include "AbilitySystem/FrozenAbilitySystemComponent.h"
#include "AbilitySystem/FrozenAttributeSet.h"


AFrozenPlayerState::AFrozenPlayerState()
{
	NetUpdateFrequency = 100.f;
	AbilitySystemComponent = CreateDefaultSubobject<UFrozenAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UFrozenAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AFrozenPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AFrozenPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}
