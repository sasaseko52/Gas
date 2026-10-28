// Copyright Mostafa Ibrahem

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "FrozenInputConfig.h"
#include "FrozenInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UFrozenInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template<class UserClass, typename PressedFuncType,typename ReleasedFuncType,typename HeldFuncType>
	void BindAbilityActions(const UFrozenInputConfig* InputConfig,UserClass* Object,PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc,HeldFuncType HeldFunc);
	
	
	
	
	
	
	
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UFrozenInputComponent::BindAbilityActions(const UFrozenInputConfig* InputConfig, UserClass* Object,PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConfig);
	
	for (const FFrozenInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.Action && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action.Action,ETriggerEvent::Started,Object,PressedFunc,Action.InputTag);
			}
			if (ReleasedFunc)
			{
				BindAction(Action.Action,ETriggerEvent::Completed,Object,ReleasedFunc,Action.InputTag);
			}
			if (HeldFunc)
			{
				BindAction(Action.Action,ETriggerEvent::Triggered,Object,HeldFunc,Action.InputTag);
			}
		}
		
	}
	
}
