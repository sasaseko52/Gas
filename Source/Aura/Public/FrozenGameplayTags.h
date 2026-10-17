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
	FGameplayTag Attribute_Secondary_CriticalHitChance;
	FGameplayTag Attribute_Secondary_CriticalHitDamage;
	FGameplayTag Attribute_Secondary_CriticalHitResistance;
	FGameplayTag Attribute_Secondary_HealthRegeneration;
	FGameplayTag Attribute_Secondary_ManaRegeneration;
	
	
	
	
	
	
	
	
	FGameplayTag Quests_Primary_GoblinQuest;
protected:
	
	
	
private:
	
	static FFrozenGameplayTags GameplayTagsInstance;
};