#pragma once

#include "GameplayEffectTypes.h"
#include "FrozenAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FFrozenGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()
	
public:
	/** Creates a copy of this context, used to duplicate for later modifications */
	virtual FFrozenGameplayEffectContext* Duplicate() const 
	{
		FFrozenGameplayEffectContext* NewContext = new FFrozenGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}
	
	virtual UScriptStruct* GetScriptStruct() const 
	{
		return StaticStruct(); 
	}
	
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override;
	
	bool IsCriticalHit()const  {return bIsBlockedHit;}
	bool IsBlockedHit()const  {return bIsBlockedHit;}
	
	void SetIsCriticalHit(bool bInCriticalHit) {bIsCriticalHit = bInCriticalHit;}
	void SetIsBlockedHit(bool bInBlockedHit) {bIsBlockedHit = bInBlockedHit;}
protected:
	
	UPROPERTY()
	bool bIsCriticalHit = false;
	
	UPROPERTY()	
	bool bIsBlockedHit = false;
};

template<>
struct TStructOpsTypeTraits<FFrozenGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FFrozenGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
	
};