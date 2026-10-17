// Copyright Mostafa Ibrahem

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FrozenHUD.generated.h"

class UQuestLogWidgetController;
class UAttributeMenuWidgetController;
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
	
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParameters& WCParams);
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParameters& WCParams);
	UQuestLogWidgetController* GetQuestLogWidegtContorller(const FWidgetControllerParameters& WCParams);
	void InitOverlay(APlayerController* PC, APlayerState* PS,UAbilitySystemComponent* ASC,  UAttributeSet* AS);
protected:
	
	
	
private:
	//Overlay Widget
	UPROPERTY()
	TObjectPtr<UFrozenUserWidget> OverlayWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UFrozenUserWidget> OverlayWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
	
	//Attribute Menu Widget
		
	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
	
	//Quest Log Widget 
	UPROPERTY()
	TObjectPtr<UQuestLogWidgetController> QuestLogWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UQuestLogWidgetController> QuestLogWidgetControllerClass;
	
};
