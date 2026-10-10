// Copyright Mostafa Ibrahem

#include "AbilitySystem/MMC/MMC_MaxHealth.h"
#include "AbilitySystem/FrozenAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	
	VigorDef.AttributeToCapture = UFrozenAttributeSet::GetVigorAttribute();
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot = false;
	
	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	//Gather Tags
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;
	float VigorValue = 0.f;
	GetCapturedAttributeMagnitude(VigorDef,Spec,EvaluateParameters,VigorValue);
	VigorValue = FMath::Max<float>(VigorValue,0.f);
	
	ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	int32 PlayerLevel=SourceCombatInterface->GetPlayerLevel();
	
	return  80.f + (2.5f * VigorValue) + (10.f * PlayerLevel);  
	
	
}
