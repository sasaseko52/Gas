// Copyright Mostafa Ibrahem

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FrozenUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UFrozenUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION()
	void SetWidgetController(UObject* InWidgetController);
	
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
	
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
