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
	
	
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities);
	
	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
	
protected:
	
	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);
	
	
	
};
