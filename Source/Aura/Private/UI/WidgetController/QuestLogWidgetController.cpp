// Copyright Mostafa Ibrahem


#include "UI/WidgetController/QuestLogWidgetController.h"
#include "AbilitySystem/QuestManagerComponent.h"
#include "Player/FrozenPlayerState.h"

void UQuestLogWidgetController::BindCallbacksToDependencies()
{
	
	GetQuestManagerComponent()->OnQuestListChangedDelegate.AddDynamic(this, &UQuestLogWidgetController::BroadcastInitialValues);
	
}
void UQuestLogWidgetController::BroadcastInitialValues()
{
	
	const TArray<FFrozenCollectionInfo> Rows = GetQuestManagerComponent()->GetAllCollections();
	FrozenQuestRowsDelegate.Broadcast(Rows);
	
}

void UQuestLogWidgetController::SelectCollection(const FGameplayTag& CollectionTag)
{
	
	const TArray<FFrozenQuestRowData> Rows = GetQuestManagerComponent()->GetQuestRowsForCollection(CollectionTag);
	
	QuestCollectionSelectedDelegate.Broadcast(CollectionTag,Rows);
}

TObjectPtr<UQuestManagerComponent> UQuestLogWidgetController::GetQuestManagerComponent()
{
	AFrozenPlayerState* FrozenPlayerState = Cast<AFrozenPlayerState>(PlayerState);
	check(FrozenPlayerState);
	return FrozenPlayerState->GetQuestManagerComponent();
}

