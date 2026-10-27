// Copyright Mostafa Ibrahem

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "QuestInfo.generated.h"

struct FGameplayTag;

USTRUCT(BlueprintType)
struct FFrozenQuestInfo
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag QuestTag = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag CollectionTag = FGameplayTag();
	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText QuestName = FText();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText QuestDescription = FText();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTexture2D> QuestIcon = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 RequiredPlayerLevel = 1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FGameplayTag> PrerequisiteQuestTags;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 SortOrder = 0;
};



UCLASS()
class AURA_API UQuestInfo : public UDataAsset
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FFrozenQuestInfo> Quests;
	
	FFrozenQuestInfo FindQuestByTag(const FGameplayTag& Tag, bool bLogNotFound = false) const;
	
};
