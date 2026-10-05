// Copyright Mostafa Ibrahem


#include "AbilitySystem/FrozenAbilitySystemComponent.h"

void UFrozenAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UFrozenAbilitySystemComponent::EffectApplied);
}

void UFrozenAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                  const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	
	FGameplayTagContainer Container;
	EffectSpec.GetAllAssetTags(Container); 
	EffectAssetTagsDelegate.Broadcast(Container);
	
}
