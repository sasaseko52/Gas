// Copyright Mostafa Ibrahem


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/FrozenAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"


void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UFrozenAttributeSet* AS = CastChecked<UFrozenAttributeSet>(AttributeSet);
	
	for (auto& Pair : AS->GameplayTagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this,Pair](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Pair.Key, Pair.Value());
			});
		
	}
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UFrozenAttributeSet* AS = CastChecked<UFrozenAttributeSet>(AttributeSet);
	check(AttributeInfo)
//		
	for (auto& Pair : AS->GameplayTagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}
	
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& GameplayTag,
	const FGameplayAttribute& Attribute)
{
	
	FFrozenAttributeInfo FrozenAttributeInfo = AttributeInfo->FindAttributeInfoForTag(GameplayTag);
	FrozenAttributeInfo.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	FrozenAttributeInfoDelegate.Broadcast(FrozenAttributeInfo);
	
}

