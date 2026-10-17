// Copyright Mostafa Ibrahem

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/FrozenWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

class UAttributeInfo;
struct FFrozenAttributeInfo;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FrozenAttributeInfoSignature, const FFrozenAttributeInfo&, Info);
UCLASS(BlueprintType, Blueprintable)		
class AURA_API UAttributeMenuWidgetController : public UFrozenWidgetController
{
	GENERATED_BODY()
	
public:
	virtual void BindCallbacksToDependencies() override;	
	
	
	virtual void BroadcastInitialValues() override;
	
	
	UPROPERTY(BlueprintAssignable,Category="GAS|AttributeInfo")
	FrozenAttributeInfoSignature FrozenAttributeInfoDelegate;
	
	
protected:
	
	UPROPERTY(EditDefaultsOnly,Category="GAS|AttributeInfo")
	TObjectPtr<UAttributeInfo> AttributeInfo;
	
};
