// Copyright Mostafa Ibrahem
#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include "FrozenGameplayTags.h"
#include "AbilitySystem/FrozenAttributeSet.h"


//internal struct
struct FrozenDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	FrozenDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFrozenAttributeSet, Armor,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFrozenAttributeSet, ArmorPenetration,Source,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFrozenAttributeSet, BlockChance,Target,false);
	}
	

	
};
static const FrozenDamageStatics&  GetFrozenDamageStatics()
{
	static FrozenDamageStatics DamageStatics;
	return DamageStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	
	RelevantAttributesToCapture.Add(GetFrozenDamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(GetFrozenDamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(GetFrozenDamageStatics().ArmorPenetrationDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
	
	
	const AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	const AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;
	
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	
	float Damage = Spec.GetSetByCallerMagnitude(FFrozenGameplayTags::Get().Damage);
	
	
			/// *** { . . . BLOCK CHANCE . . .}  ***
	float TargetBlockChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetFrozenDamageStatics().BlockChanceDef,EvaluateParameters,TargetBlockChance);
	TargetBlockChance = FMath::Max<float>(TargetBlockChance,0.f);
	
	const bool bBlocked = FMath::RandRange(1,100) < TargetBlockChance;
	
	if (bBlocked)
	{
		Damage = Damage/2.f;
	}
	
			/// *** { . . . Target Armor . . .}  ***
	float TargetArmor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetFrozenDamageStatics().ArmorDef,EvaluateParameters,TargetArmor);
	TargetArmor = FMath::Max<float>(TargetArmor,0.f);
	
			/// *** { . . . Source Armor Penetration . . .}  ***
	float SourceArmorPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetFrozenDamageStatics().ArmorPenetrationDef,EvaluateParameters,SourceArmorPenetration);
	SourceArmorPenetration = FMath::Max<float>(SourceArmorPenetration,0.f);
	
	
	
	const float EffectiveArmor = TargetArmor *= (100 - SourceArmorPenetration * .25f) / 100.f;
	
	
	
	Damage *= (100 - EffectiveArmor) / 100.f;
	
	
	
	
	
	
	FGameplayModifierEvaluatedData ModifierData(UFrozenAttributeSet::GetIncomingDamageAttribute(),EGameplayModOp::Additive,Damage);
	
	OutExecutionOutput.AddOutputModifier(ModifierData);
	
	
	
	
}
