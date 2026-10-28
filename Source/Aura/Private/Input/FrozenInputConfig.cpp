// Copyright Mostafa Ibrahem


#include "Input/FrozenInputConfig.h"

const UInputAction* UFrozenInputConfig::FindAbilityInputForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	
	for (const FFrozenInputAction& AbilityAction : AbilityInputActions)
	{
		if (AbilityAction.InputTag.MatchesTag(InputTag) && AbilityAction.Action)
		{
			return AbilityAction.Action;
		}
	}
	
	if (bLogNotFound)
	{
		UE_LOG(LogTemp,Warning,TEXT("Cant find ability input action for inputTag"));
	}
	return nullptr;
}
