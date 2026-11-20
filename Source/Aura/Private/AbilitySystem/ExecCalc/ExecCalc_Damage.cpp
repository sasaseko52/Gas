// Copyright Mostafa Ibrahem
#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include "FrozenGameplayTags.h"
#include "AbilitySystem/FrozenAbilitySystemLibrary.h"
#include "AbilitySystem/FrozenAttributeSet.h"
#include "Interaction/CombatInterface.h"


//internal struct
struct FrozenDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);
	FrozenDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFrozenAttributeSet, Armor,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFrozenAttributeSet, ArmorPenetration,Source,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFrozenAttributeSet, BlockChance,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFrozenAttributeSet, CriticalHitChance,Source,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFrozenAttributeSet, CriticalHitDamage,Source,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFrozenAttributeSet, CriticalHitResistance,Target,false);
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
	RelevantAttributesToCapture.Add(GetFrozenDamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(GetFrozenDamageStatics().CriticalHitDamageDef);
	RelevantAttributesToCapture.Add(GetFrozenDamageStatics().CriticalHitResistanceDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
	
	
	 AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	 AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;
	ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceAvatar);
	ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetAvatar);
	
	
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
	
	
	
	
	UCharacterClassInfo* CharacterClassInfo = UFrozenAbilitySystemLibrary::GetCharacterClassInfo(SourceAvatar);
	
	FRealCurve* ArmorPenetrationCoCurve =CharacterClassInfo->DamageCoefficient->FindCurve(FName("ArmorPenetrationCo"),FString());
	float ArmorPenetrationCo = ArmorPenetrationCoCurve->Eval(SourceCombatInterface->GetPlayerLevel());
	
	
	const float EffectiveArmor = TargetArmor * (100 - SourceArmorPenetration * ArmorPenetrationCo) / 100.f;
	
	FRealCurve* EffectiveArmorCurve = CharacterClassInfo->DamageCoefficient->FindCurve(FName("EffectiveArmorCo"),FString());
	float EffectiveArmorCo = EffectiveArmorCurve->Eval(TargetCombatInterface->GetPlayerLevel());
	
	
	Damage *= (100 - EffectiveArmor * EffectiveArmorCo) / 100.f;
	
	/// *** { . . . Source Critical Hit Chance & Damage. . .}  ***
	float SourceCriticalHitChance = 0.f;
	float SourceCriticalHitDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetFrozenDamageStatics().CriticalHitChanceDef,EvaluateParameters,SourceCriticalHitChance);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetFrozenDamageStatics().CriticalHitDamageDef,EvaluateParameters,SourceCriticalHitDamage);
	/// *** { . . . Target Critical HitResistance. . .}  ***
	float TargetCriticalHitResistance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetFrozenDamageStatics().CriticalHitResistanceDef,EvaluateParameters,TargetCriticalHitResistance);
	
	float EffectiveCriticalHitResistance = SourceCriticalHitChance - (.1 * TargetCriticalHitResistance);
	
	bool bCriticalHit = FMath::RandRange(1,10) < EffectiveCriticalHitResistance;
	
	if (bCriticalHit)
	{
		Damage = (Damage * 2.f ) + SourceCriticalHitDamage;
	}
	
	
	FGameplayModifierEvaluatedData ModifierData(UFrozenAttributeSet::GetIncomingDamageAttribute(),EGameplayModOp::Additive,Damage);
	
	OutExecutionOutput.AddOutputModifier(ModifierData);
	
	
	
	
}
