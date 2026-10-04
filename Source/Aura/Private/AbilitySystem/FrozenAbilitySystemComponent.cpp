// Copyright Mostafa Ibrahem


#include "AbilitySystem/FrozenAbilitySystemComponent.h"

void UFrozenAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UFrozenAbilitySystemComponent::EffectApplied);
}

void UFrozenAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                  const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	
	GEngine->AddOnScreenDebugMessage(1,8.f,FColor::Green,FString("Effect Applied!!"));
	
}
