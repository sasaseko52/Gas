// Copyright Mostafa Ibrahem


#include "AbilitySystem/Data/QuestInfo.h"

FFrozenQuestInfo UQuestInfo::FindQuestByTag(const FGameplayTag& Tag, bool bLogNotFound) const
{
	for (const FFrozenQuestInfo& QuestInfo : Quests)
	{
		if (QuestInfo.QuestTag == Tag)
		{
			return QuestInfo;
		}
		
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Attribute tag not found: %s  on %s"), *Tag.ToString(),*GetNameSafe(this));
	}
	return FFrozenQuestInfo();	
	
}
