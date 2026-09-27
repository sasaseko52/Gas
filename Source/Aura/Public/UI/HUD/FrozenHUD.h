// Copyright Mostafa Ibrahem

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FrozenHUD.generated.h"

struct FWidgetControllerParameters;
class UOverlayWidgetController;
class UFrozenUserWidget;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class AURA_API AFrozenHUD : public AHUD
{
	GENERATED_BODY()
public:
	
	UPROPERTY(BlueprintReadOnly, Category = "Widget")
	TObjectPtr<UFrozenUserWidget> OverlayWidget;
	
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParameters& WCParams);
	
	
	void InitOverlay(APlayerController* PC, APlayerState* PS,UAbilitySystemComponent* ASC,  UAttributeSet* AS);
protected:
	
	
	
private:
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UFrozenUserWidget> OverlayWidgetClass;
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
	
	
};
