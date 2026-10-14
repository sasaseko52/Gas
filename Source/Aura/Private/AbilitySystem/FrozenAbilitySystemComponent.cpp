// Copyright Mostafa Ibrahem


#include "AbilitySystem/FrozenAbilitySystemComponent.h"

#include "FrozenGameplayTags.h"

void UFrozenAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UFrozenAbilitySystemComponent::EffectApplied);
	
	const FFrozenGameplayTags& GameplayTags = FFrozenGameplayTags::Get();
	//GameplayTags.Attributes_Secondary_Armor.ToString();
	
	//GEngine->AddOnScreenDebugMessage(-1,10,FColor::Green,FString::Printf(TEXT("%s"),*GameplayTags.Attributes_Secondary_Armor.ToString()));
	
}

void UFrozenAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                  const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	
	FGameplayTagContainer Container;
	EffectSpec.GetAllAssetTags(Container); 
	EffectAssetTagsDelegate.Broadcast(Container);
	
}
