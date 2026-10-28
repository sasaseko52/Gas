// Copyright Mostafa Ibrahem


#include "FrozenGameplayTags.h"
#include "GameplayTagsManager.h"

FFrozenGameplayTags FFrozenGameplayTags::GameplayTagsInstance;

void FFrozenGameplayTags::InitializeNativeGameplayTags()
{
	
	//Primary 
GameplayTagsInstance.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength"),FString("Strength"));
GameplayTagsInstance.Attributes_Primary_Vigor =	UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vigor"),FString("Vigor"));
GameplayTagsInstance.Attributes_Primary_Intelligence =UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"),FString("Intelligence"));
GameplayTagsInstance.Attributes_Primary_Resilience=	UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Resilience"),FString("Resilience"));
	//Secondary
GameplayTagsInstance.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"),FString("MaxHealth"));
GameplayTagsInstance.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"),FString("MaxMana"));
GameplayTagsInstance.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"),FString("Armor"));
GameplayTagsInstance.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"),FString("ArmorPenetration"));
GameplayTagsInstance.Attributes_Secondary_BlockChance = 	UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.BlockChance"),FString("BlockChance"));
GameplayTagsInstance.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitChance"),FString("CriticalHitChance"));
GameplayTagsInstance.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitDamage"),FString("CriticalHitDamage"));
GameplayTagsInstance.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitResistance"),FString("CriticalHitResistance"));
GameplayTagsInstance.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration"),FString("HealthRegeneration"));
GameplayTagsInstance.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration"),FString("ManaRegeneration"));
	
	//InputTags
	
	GameplayTagsInstance.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.LMB"),FString("LMB"));	
	GameplayTagsInstance.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.RMB"),FString("RMB"));
	GameplayTagsInstance.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.1"),FString("1"));
	GameplayTagsInstance.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.2"),FString("2"));
	GameplayTagsInstance.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.3"),FString("3"));
	GameplayTagsInstance.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.4"),FString("4"));
	
	
	
	
	//Quest Collection Tags 
GameplayTagsInstance.QuestCollection_Goblin = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("QuestCollection.Goblin"),FString("Goblin Quest Collection"));
GameplayTagsInstance.QuestCollection_Skeleton = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("QuestCollection.Skeleton"),FString("Skeleton Quest Collection"));
GameplayTagsInstance.QuestCollection_Demon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("QuestCollection.Demon"),FString("Demon Quest Collection"));
GameplayTagsInstance.QuestCollection_Forest = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("QuestCollection.Forest"),FString("Forest Quest Collection"));
	
	//Quest Tags
GameplayTagsInstance.Quest_Goblin_GoblinExtermination = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Quest.Goblin.GoblinExtermination"),FString("GoblinExtermination"));
GameplayTagsInstance.Quest_Goblin_GoblinSecond = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Quest.Goblin.GoblinSecond"),FString("GoblinSecond"));
	
GameplayTagsInstance.Quest_Skeleton_SkeletonHunt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Quest.Skeleton.Hunt"),FString("Hunt"));
GameplayTagsInstance.Quest_Skeleton_DemonicSkeleton = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Quest.Skeleton.DemonicSkeleton"),FString("Hunt"));
	
	
GameplayTagsInstance.Quest_Forest_Wolves =  UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Quest.Forest.Wolves"),FString("Wolves Hunt"));
	
GameplayTagsInstance.Quest_Demon_DemonCatch = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Quest.Demon.DemonCatch"),FString("DemonCatch"));
	
GameplayTagsInstance.Quest_Demon_DemonMinionCatch = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Quest.Demon.DemonMinionCatch"),FString("DemonMinionCatch"));	
	
}

