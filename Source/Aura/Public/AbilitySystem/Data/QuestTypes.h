// Copyright Mostafa Ibrahem

#pragma once

#include "CoreMinimal.h"
#include "QuestInfo.h"
#include "QuestTypes.generated.h"

UENUM(BlueprintType)
enum class EFrozenQuestStatus : uint8
{
	Locked,
	Available,
	Active,
	Completed,
	Failed	
};

USTRUCT(BlueprintType)
struct FFrozenQuestRunTimeState
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayTag QuestTag;
	
	UPROPERTY(BlueprintReadOnly)
	EFrozenQuestStatus Status = EFrozenQuestStatus::Locked;

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentProgress = 0;
	
	UPROPERTY(BlueprintReadOnly)
	int32 RequiredProgress = 1;
};

USTRUCT(BlueprintType)
struct FFrozenQuestRowData
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly)
	FFrozenQuestInfo QuestInfo;
	
	UPROPERTY(BlueprintReadOnly)
	EFrozenQuestStatus Status = EFrozenQuestStatus::Locked;
	
	UPROPERTY(BlueprintReadOnly)
	int32 CurrentProgress = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 RequiredProgress = 1;
};