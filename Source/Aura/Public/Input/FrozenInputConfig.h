// Copyright Mostafa Ibrahem

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "FrozenInputConfig.generated.h"

USTRUCT(BlueprintType)
struct FFrozenInputAction
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* Action = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
		
};


UCLASS()
class AURA_API UFrozenInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	
	
	const UInputAction* FindAbilityInputForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "AbilityInput")
	TArray<FFrozenInputAction> AbilityInputActions;
	
	
	
};
