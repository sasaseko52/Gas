// Copyright Mostafa Ibrahem


#include "AbilitySystem/FrozenAttributeSet.h"
#include"AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

UFrozenAttributeSet::UFrozenAttributeSet()
{
	InitHealth(100.f);
	InitMaxHealth(100.f);
	InitMana(100.f);
	InitMaxMana(100.f);
}

void UFrozenAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UFrozenAttributeSet,Health,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFrozenAttributeSet,MaxHealth,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFrozenAttributeSet,Mana,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFrozenAttributeSet,MaxMana,COND_None,REPNOTIFY_Always);
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
