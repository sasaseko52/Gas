// Copyright Mostafa Ibrahem


#include "AbilitySystem/FrozenAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include"AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UFrozenAttributeSet::UFrozenAttributeSet()
{
	InitHealth(10.f);

	InitMaxMana(10.f);
	
	
}

void UFrozenAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UFrozenAttributeSet,Health,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFrozenAttributeSet,MaxHealth,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFrozenAttributeSet,Mana,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFrozenAttributeSet,MaxMana,COND_None,REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UFrozenAttributeSet,Intelligence,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFrozenAttributeSet,Strength,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFrozenAttributeSet,Vigor,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFrozenAttributeSet,Resilience,COND_None,REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UFrozenAttributeSet,Armor,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFrozenAttributeSet,ArmorPenetration,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFrozenAttributeSet,BlockChance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFrozenAttributeSet,CriticalHitChance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFrozenAttributeSet,CriticalHitDamage,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFrozenAttributeSet,CriticalHitResistance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFrozenAttributeSet,HealthRegeneration,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFrozenAttributeSet,ManaRegeneration,COND_None,REPNOTIFY_Always);
	
	
	
	
}




void UFrozenAttributeSet::SetEffectProperties(FEffectProperties& EffectProperties,
                                              const FGameplayEffectModCallbackData& Data)
{
	EffectProperties.EffectContextHandle = Data.EffectSpec.GetContext();
	 
	
	EffectProperties.SourceAbilitySystemComponent = EffectProperties.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	
	if (IsValid(EffectProperties.SourceAbilitySystemComponent) && IsValid(EffectProperties.SourceAbilitySystemComponent->GetAvatarActor()) &&  EffectProperties.SourceAbilitySystemComponent->AbilityActorInfo.IsValid())
	{
		EffectProperties.SourceAvatarActor = EffectProperties.SourceAbilitySystemComponent->GetAvatarActor();
		EffectProperties.SourceController = EffectProperties.SourceAbilitySystemComponent->AbilityActorInfo->PlayerController.Get();
		if (EffectProperties.SourceController== nullptr && EffectProperties.SourceAvatarActor  != nullptr)
		{
			if (APawn* Pawn = Cast<APawn>(EffectProperties.SourceAvatarActor ))
			{
				EffectProperties.SourceController = Pawn->GetController();
			}
		}
		if (EffectProperties.SourceController)
		{
			EffectProperties.SourceCharacter = EffectProperties.SourceController->GetCharacter();
		}
	}
	
	if (Data.Target.GetAvatarActor() && Data.Target.AbilityActorInfo.IsValid())
	{
		EffectProperties.TargetAvatarActor = Data.Target.GetAvatarActor();
		EffectProperties.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		EffectProperties.TargetCharacter = EffectProperties.TargetController->GetCharacter();
		EffectProperties.TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(EffectProperties.TargetAvatarActor);
	}
}
void UFrozenAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	FEffectProperties EffectProps;
	SetEffectProperties(EffectProps,Data);
	
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(),0.f,GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(),0.f,GetMaxMana()));
	}
}



void UFrozenAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFrozenAttributeSet,Health, OldHealth);
	
}

void UFrozenAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFrozenAttributeSet,MaxHealth, OldMaxHealth);
}

void UFrozenAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFrozenAttributeSet,Mana, OldMana);
}

void UFrozenAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFrozenAttributeSet,MaxMana, OldMaxMana);
}
void UFrozenAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFrozenAttributeSet,Strength, OldStrength)
}
void UFrozenAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFrozenAttributeSet,Intelligence, OldIntelligence)
}
void UFrozenAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFrozenAttributeSet,Vigor, OldVigor)
}
void UFrozenAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFrozenAttributeSet,Resilience, OldResilience)
}

void UFrozenAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFrozenAttributeSet,Armor, OldArmor)
}

void UFrozenAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFrozenAttributeSet,ArmorPenetration, OldArmorPenetration)
}

void UFrozenAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFrozenAttributeSet,BlockChance, OldBlockChance)
}

void UFrozenAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFrozenAttributeSet,CriticalHitChance, OldCriticalHitChance)
}

void UFrozenAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFrozenAttributeSet,CriticalHitDamage, OldCriticalHitDamage)
}

void UFrozenAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFrozenAttributeSet,CriticalHitResistance, OldCriticalHitResistance)
}

void UFrozenAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFrozenAttributeSet,HealthRegeneration, OldHealthRegeneration)
}

void UFrozenAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFrozenAttributeSet,ManaRegeneration, OldManaRegeneration)
}
