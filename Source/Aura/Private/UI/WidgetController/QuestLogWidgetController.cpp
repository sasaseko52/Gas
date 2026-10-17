// Copyright Mostafa Ibrahem


#include "UI/WidgetController/QuestLogWidgetController.h"

#include "FrozenGameplayTags.h"
#include "AbilitySystem/Data/QuestInfo.h"

void UQuestLogWidgetController::BindCallbacksToDependencies()
{
	
}
void UQuestLogWidgetController::BroadcastInitialValues()
{
	check(QuestInfo)
	
	FFrozenQuestInfo Info = QuestInfo->FindQuestByTag(FFrozenGameplayTags::Get().Quests_Primary_GoblinQuest);
	
	FrozenQuestInfoDelegate.Broadcast(Info);
}
