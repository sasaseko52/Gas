// Copyright Mostafa Ibrahem


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/FrozenAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UFrozenAttributeSet* FrozenAttributeSet = CastChecked<UFrozenAttributeSet>(AttributeSet);
	OnHealthChangedDelegate.Broadcast(FrozenAttributeSet->GetHealth());
	OnMaxHealthChangedDelegate.Broadcast(FrozenAttributeSet->GetMaxHealth());
	
}
