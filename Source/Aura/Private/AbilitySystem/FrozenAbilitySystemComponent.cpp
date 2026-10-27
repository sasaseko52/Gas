// Copyright Mostafa Ibrahem


#include "AbilitySystem/FrozenAbilitySystemComponent.h"

#include "FrozenGameplayTags.h"

void UFrozenAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UFrozenAbilitySystemComponent::EffectApplied);
	
	const FFrozenGameplayTags& GameplayTags = FFrozenGameplayTags::Get();
	
	
}

void UFrozenAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities)
{
	for ( TSubclassOf<UGameplayAbility> Ability : Abilities)
	{
		FGameplayAbilitySpec AbilitySpec =	FGameplayAbilitySpec(Ability,1);
		
		GiveAbilityAndActivateOnce(AbilitySpec);
			
	}
	
	
	
	
	
}

void UFrozenAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                  const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	
	FGameplayTagContainer Container;
	EffectSpec.GetAllAssetTags(Container); 
	EffectAssetTagsDelegate.Broadcast(Container);
	
}
