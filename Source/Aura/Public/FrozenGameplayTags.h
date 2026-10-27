// Copyright Mostafa Ibrahem

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

// SINGLETON **Native Gameplay Tags


struct FFrozenGameplayTags
{
public:
	
	static const FFrozenGameplayTags& Get()
	{
		
		return GameplayTagsInstance;
	}
	
	static void InitializeNativeGameplayTags();
	
	
	
	
	
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Vigor;
	FGameplayTag Attributes_Primary_Resilience;
	
	
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;
	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	
	
	
	
	
	
	FGameplayTag QuestCollection_Goblin;
	FGameplayTag QuestCollection_Skeleton;
	FGameplayTag QuestCollection_Forest;
	FGameplayTag QuestCollection_Demon;
	
	
	FGameplayTag Quest_Goblin_GoblinExtermination;
	FGameplayTag Quest_Goblin_GoblinSecond;
	
	FGameplayTag Quest_Skeleton_SkeletonHunt;
	FGameplayTag Quest_Skeleton_DemonicSkeleton;
	
	FGameplayTag Quest_Demon_DemonCatch;
	FGameplayTag Quest_Demon_DemonMinionCatch;
	
	FGameplayTag Quest_Forest_Wolves;
	
protected:
	
	
	
private:
	
	static FFrozenGameplayTags GameplayTagsInstance;
};