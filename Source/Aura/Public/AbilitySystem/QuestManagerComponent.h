// Copyright Mostafa Ibrahem

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "Data/QuestTypes.h"
#include "QuestManagerComponent.generated.h"

struct FFrozenQuestInfo;
struct FFrozenCollectionInfo;

struct FFrozenQuestRowData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuestListChangedSignature);

struct FGameplayTag;
class UQuestCollectionInfo;
class UQuestInfo;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AURA_API UQuestManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UQuestManagerComponent();
	
	UPROPERTY(BlueprintAssignable,  Category= "Quest")
	FOnQuestListChangedSignature OnQuestListChangedDelegate;
	

	UFUNCTION(BlueprintCallable , Category= "Quest")
	void InitializeQuestStates();
	
	UFUNCTION(BlueprintCallable, Category="Quests")
	bool ActivateQuest(const FGameplayTag& QuestTag);
	
	UFUNCTION( BlueprintCallable , Category= "Quest")
	void RefreshQuestProgression(int32 PlayerLevel);
	
	UFUNCTION( BlueprintCallable , Category= "Quest")
	bool CompleteQuest(const FGameplayTag& QuestTag);
	
	UFUNCTION(BlueprintPure, Category="Quests")
	TArray<FFrozenQuestRowData> GetSelectedCollectionQuestRows()const;
	
	UFUNCTION(BlueprintCallable, Category="Quests")
	TArray<FFrozenQuestRowData> GetQuestRowsForCollection(const FGameplayTag& CollectionTag)const;
	
	UFUNCTION(BlueprintCallable, Category="Quests")
	TArray<FFrozenCollectionInfo> GetAllCollections()const;
	
	
	
	UFUNCTION(BlueprintPure, Category="Quests")
	FGameplayTag GetSelectedQuestCollectionTag()const
	{
		return SelectedCollectionTag;
	}
	
	
protected:
	UPROPERTY()
	FGameplayTag SelectedCollectionTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
	TObjectPtr<UQuestInfo> QuestInfoAsset;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
	TObjectPtr<UQuestCollectionInfo> QuestCollectionAsset;
		
private:
	UPROPERTY()
	TMap<FGameplayTag,FFrozenQuestRunTimeState> QuestStates;
	
	int32 CachedPlayerLevel = 1;
	
	
	bool IsQuestAvailable(const FFrozenQuestInfo& Quest) const;
	
	bool ArePrerequisiteQuestsCompleted(const TArray<FGameplayTag>& Prerequisites) const;
		
	bool IsCollectionCompleted(const FFrozenCollectionInfo& Collection) const;
	
	void UpdateQuestStatuses();
	
	const FFrozenCollectionInfo* SelectCurrentCollection() const;
	
	
	
	
};
