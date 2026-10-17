// Copyright Mostafa Ibrahem


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/FrozenAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "FrozenGameplayTags.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UFrozenAttributeSet* AS = CastChecked<UFrozenAttributeSet>(AttributeSet);
	
	
	check(AttributeInfo)
	FFrozenAttributeInfo FrozenAttributeInfo = AttributeInfo->FindAttributeInfoForTag(FFrozenGameplayTags::Get().Attributes_Primary_Strength);
	FrozenAttributeInfo.AttributeValue = AS->GetStrength();
	
	FrozenAttributeInfoDelegate.Broadcast(FrozenAttributeInfo);
}
