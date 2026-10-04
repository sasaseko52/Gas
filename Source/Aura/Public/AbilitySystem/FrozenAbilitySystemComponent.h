// Copyright Mostafa Ibrahem

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "FrozenAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UFrozenAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	
	void AbilityActorInfoSet();
	
protected:
	
	
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);
	
	
	
};
