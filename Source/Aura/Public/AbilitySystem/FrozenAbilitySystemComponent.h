// Copyright Mostafa Ibrahem

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "FrozenAbilitySystemComponent.generated.h"

 DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTagsSignature,const FGameplayTagContainer&);
/**
 * 
 */
UCLASS()
class AURA_API UFrozenAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	
	void AbilityActorInfoSet();
	FEffectAssetTagsSignature EffectAssetTagsDelegate;
protected:
	
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);
	
	
	
};
