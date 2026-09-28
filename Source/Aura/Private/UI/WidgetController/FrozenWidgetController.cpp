// Copyright Mostafa Ibrahem


#include "UI/WidgetController/FrozenWidgetController.h"

void UFrozenWidgetController::SetWidgetControllerParameters(const FWidgetControllerParameters& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
	
}

void UFrozenWidgetController::BroadcastInitialValues()
{
	
}

void UFrozenWidgetController::BindCallbacksToDependencies()
{
	
}
