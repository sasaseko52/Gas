// Copyright Mostafa Ibrahem

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/BaseGameplayAbility.h"
#include "ProjectileSpellGameplayAbility.generated.h"


class AFrozenProjectile;

UCLASS()
class AURA_API UProjectileSpellGameplayAbility : public UBaseGameplayAbility
{
	GENERATED_BODY()
	
protected:
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<AFrozenProjectile> ProjectileClass;
	
};
