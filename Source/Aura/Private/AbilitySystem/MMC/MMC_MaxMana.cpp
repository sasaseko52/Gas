// Copyright Mostafa Ibrahem


#include "AbilitySystem/MMC/MMC_MaxMana.h"

#include "AbilitySystem/FrozenAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntelligenceDef.AttributeToCapture = UFrozenAttributeSet::GetIntelligenceAttribute();
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDef.bSnapshot = false; 
	RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	//Gather Tags
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;
	
	float IntelligenceValue = 0.f;
	
	GetCapturedAttributeMagnitude(IntelligenceDef,Spec,EvaluateParameters,IntelligenceValue);
	IntelligenceValue = FMath::Max<float>(IntelligenceValue,0.f);
	
	ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(Spec.GetEffectContext().GetSourceObject());
	int32 PlayerLevel = SourceCombatInterface->GetPlayerLevel();
	
	return 50.f +(1.5f * IntelligenceValue) + (5 * PlayerLevel);
}
