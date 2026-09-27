// Copyright Mostafa Ibrahem

#pragma once
#include "CoreMinimal.h"
#include "UI/WidgetController/FrozenWidgetController.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature,float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature,float, NewMaxHealth);




UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UFrozenWidgetController
{
	GENERATED_BODY()
public:
	
	virtual void BroadcastInitialValues()override;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHealthChangedSignature OnHealthChangedDelegate;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChangedDelegate;
	
};
