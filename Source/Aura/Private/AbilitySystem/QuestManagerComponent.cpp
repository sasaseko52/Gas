// Copyright Mostafa Ibrahem


#include "AbilitySystem/QuestManagerComponent.h"
#include "AbilitySystem/Data/QuestCollectionInfo.h"
#include "AbilitySystem/Data/QuestInfo.h"
#include "AbilitySystem/Data/QuestTypes.h"

UQuestManagerComponent::UQuestManagerComponent()
{
	
	PrimaryComponentTick.bCanEverTick = false;


}

void UQuestManagerComponent::InitializeQuestStates()
{
	QuestStates.Empty();
	SelectedCollectionTag = FGameplayTag();
	
	if (!QuestInfoAsset) return;
	
	//Go through the Array of quests added to the 
	for (const FFrozenQuestInfo& Quest : QuestInfoAsset->Quests)
	{
		
		//Skip Any Quest that has no valid tag
		if (!Quest.QuestTag.IsValid()) continue;
		
		//Create a separate record for the player progress for each quest
		FFrozenQuestRunTimeState State;
		State.QuestTag = Quest.QuestTag;
		State.Status = EFrozenQuestStatus::Locked;
		
		QuestStates.Add(Quest.QuestTag,State);
		
	}
	
	RefreshQuestProgression(CachedPlayerLevel);
	
}

bool UQuestManagerComponent::ActivateQuest(const FGameplayTag& QuestTag)
{
	FFrozenQuestRunTimeState* State = QuestStates.Find(QuestTag);
	if (!State || State->Status != EFrozenQuestStatus::Available) return false;
	
	State->Status = EFrozenQuestStatus::Active;
	OnQuestListChangedDelegate.Broadcast();
	return true;
}

void UQuestManagerComponent::RefreshQuestProgression(int32 PlayerLevel)
{
	CachedPlayerLevel = FMath::Max(CachedPlayerLevel, PlayerLevel);
	
	UpdateQuestStatuses();
	
	const FFrozenCollectionInfo* Collection = SelectCurrentCollection();
	
	SelectedCollectionTag = Collection ? Collection->CollectionTag : FGameplayTag();
	
	UE_LOG(
		LogTemp,
		Warning,
		TEXT("Selected Collection: %s"),
		*SelectedCollectionTag.ToString()
	);
	OnQuestListChangedDelegate.Broadcast();
	
	
}
void UQuestManagerComponent::UpdateQuestStatuses()
{
	if (!QuestInfoAsset) return;
	for (const FFrozenQuestInfo& Quest : QuestInfoAsset->Quests)
	{
		FFrozenQuestRunTimeState* State = QuestStates.Find(Quest.QuestTag);
		
		if (!State) continue;
		
		if (State->Status == EFrozenQuestStatus::Completed 
			|| State->Status == EFrozenQuestStatus::Failed
			|| State->Status == EFrozenQuestStatus::Active) continue;
		
		//Check if the Quest Available or not 
		State->Status = IsQuestAvailable(Quest) ? EFrozenQuestStatus::Available : EFrozenQuestStatus::Locked;
		
	}
		
}

bool UQuestManagerComponent::CompleteQuest(const FGameplayTag& QuestTag)
{
	//Find status of this Quest
	FFrozenQuestRunTimeState* State = QuestStates.Find(QuestTag);
	
	//if it's not Active return false
	if (!State || State->Status != EFrozenQuestStatus::Active) return false;
	
	//Make the Current Progress equals the required 0->1
	State->CurrentProgress = State->RequiredProgress;
	
	//Make the quest status marked as Completed
	State->Status = EFrozenQuestStatus::Completed;
	
	RefreshQuestProgression(CachedPlayerLevel);
	return true;
}

TArray<FFrozenQuestRowData> UQuestManagerComponent::GetSelectedCollectionQuestRows() const
{
	TArray<FFrozenQuestRowData> Rows;
	
	if (!QuestInfoAsset || !SelectedCollectionTag.IsValid())  
		{    		
			return Rows;
		}
	
	
	for (const FFrozenQuestInfo& Quest : QuestInfoAsset->Quests)
	{
		
		if (Quest.CollectionTag != SelectedCollectionTag)
		{
			
			continue;
		}
		
		const FFrozenQuestRunTimeState* State = QuestStates.Find(Quest.QuestTag);
		if (!State)
		{
		
			continue;
		}
		
		FFrozenQuestRowData Row;
		
		Row.QuestInfo = Quest;
		Row.Status = State->Status;
		Row.CurrentProgress = State->CurrentProgress;
		Row.RequiredProgress = State->RequiredProgress;
		Rows.Add(Row);		
	
	}
	Rows.Sort([](const FFrozenQuestRowData& L, const FFrozenQuestRowData& R)
	{
		return L.QuestInfo.SortOrder < R.QuestInfo.SortOrder;
	});
		
	return Rows;
}

TArray<FFrozenQuestRowData> UQuestManagerComponent::GetQuestRowsForCollection(const FGameplayTag& CollectionTag) const
{
	TArray<FFrozenQuestRowData> Rows;
	if (!QuestInfoAsset ||!CollectionTag.IsValid() ) return Rows;
	
	for (const FFrozenQuestInfo& Quest : QuestInfoAsset->Quests)
	{
		if (Quest.CollectionTag != CollectionTag) continue;
		
		const FFrozenQuestRunTimeState* State = QuestStates.Find(Quest.QuestTag);
		if (!State) continue;
		
		FFrozenQuestRowData Row;
		Row.QuestInfo = Quest;
		Row.Status = State->Status;
		Row.CurrentProgress = State->CurrentProgress;
		Row.RequiredProgress = State->RequiredProgress;
		Rows.Add(Row);
	}
	Rows.Sort([](const FFrozenQuestRowData& L, const FFrozenQuestRowData& R)
	{
		return L.QuestInfo.SortOrder < R.QuestInfo.SortOrder;
	});
	
	
	return Rows;
}

TArray<FFrozenCollectionInfo> UQuestManagerComponent::GetAllCollections() const
{
	
	if (!QuestCollectionAsset) return {};
	return QuestCollectionAsset->Collections;
}



bool UQuestManagerComponent::IsQuestAvailable(const FFrozenQuestInfo& Quest) const
{
	//return true if the player level is met Required Level & the Quest Pre-requisite tags are ready
	 return CachedPlayerLevel >= Quest.RequiredPlayerLevel && ArePrerequisiteQuestsCompleted(Quest.PrerequisiteQuestTags);
}

bool UQuestManagerComponent::ArePrerequisiteQuestsCompleted(const TArray<FGameplayTag>& Prerequisites) const
{
	for (const FGameplayTag& Tag : Prerequisites)
	{
		const FFrozenQuestRunTimeState* State = QuestStates.Find(Tag);
		if (!State || State->Status != EFrozenQuestStatus::Completed) return false;
		
	}
	
	
	return true;
}

bool UQuestManagerComponent::IsCollectionCompleted(const FFrozenCollectionInfo& Collection) const
{
	if (Collection.QuestTags.IsEmpty()) return false; 
	// search in the Collection if all quested marked as completed
	
	for (const FGameplayTag& QuestTag : Collection.QuestTags)
	{
		const FFrozenQuestRunTimeState* State = QuestStates.Find(QuestTag);
		if (!State || State->Status != EFrozenQuestStatus::Completed) return false;
				
	}
		
	return true;
}


const FFrozenCollectionInfo* UQuestManagerComponent::SelectCurrentCollection() const
{
	if (!QuestCollectionAsset) return nullptr;
	
	// Empty Ptr for the Current Collection
	const FFrozenCollectionInfo* BestCollection = nullptr;
	
	//Search for the best collection in the Collection Asset Manager
	for (const FFrozenCollectionInfo& Collection : QuestCollectionAsset->Collections)
	{
		// if the Player Level not Met Pass this Collection
		if (CachedPlayerLevel < Collection.RequiredPlayerLevel) continue;
		
		// if the Prerequisites are not found Pass
		if (!ArePrerequisiteQuestsCompleted(Collection.PrerequisiteQuestTags)) continue;
		
		// if the collection is completed before Pass
		if (IsCollectionCompleted(Collection)) continue;
		
		// if the Best Collection is not filled yet or this Collection  Priority is larger than the Chosen : Chose this Collection to be the Best one to Select.
		if (!BestCollection || Collection.Priority > BestCollection->Priority)
		{
			BestCollection = &Collection;
		}
		
	}
		
	return BestCollection;
}




