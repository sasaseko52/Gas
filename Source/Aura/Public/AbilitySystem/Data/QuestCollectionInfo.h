// Copyright Mostafa Ibrahem

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "QuestCollectionInfo.generated.h"


USTRUCT(BlueprintType)
struct FFrozenCollectionInfo
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag CollectionTag = FGameplayTag();
	
	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText CollectionName = FText();
	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTexture2D> QuestIcon = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 RequiredPlayerLevel = 1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FGameplayTag> PrerequisiteQuestTags;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Priority = 0;
	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FGameplayTag> QuestTags;
};

UCLASS()
class AURA_API UQuestCollectionInfo : public UDataAsset
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FFrozenCollectionInfo> Collections;
	
};
