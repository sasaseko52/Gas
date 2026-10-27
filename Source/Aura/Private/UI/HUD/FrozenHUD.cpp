// Copyright Mostafa Ibrahem


#include "UI/HUD/FrozenHUD.h"
#include "UI/Widget/FrozenUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/WidgetController/QuestLogWidgetController.h"


UOverlayWidgetController* AFrozenHUD::GetOverlayWidgetController(const FWidgetControllerParameters& WCParams)
{
	//Overlay Widget Controller Creation
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this , OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParameters(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();
		
	}
	return OverlayWidgetController;
}

UAttributeMenuWidgetController* AFrozenHUD::GetAttributeMenuWidgetController(
	const FWidgetControllerParameters& WCParams)
{
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParameters(WCParams);
		AttributeMenuWidgetController->BindCallbacksToDependencies();
		
	}
	return AttributeMenuWidgetController;
}

UQuestLogWidgetController* AFrozenHUD::GetQuestLogWidgetController(const FWidgetControllerParameters& WCParams)
{
	if (QuestLogWidgetController == nullptr)
	{
		QuestLogWidgetController = NewObject<UQuestLogWidgetController>(this, QuestLogWidgetControllerClass);
		QuestLogWidgetController->SetWidgetControllerParameters(WCParams);
		QuestLogWidgetController->BindCallbacksToDependencies();
	}
	return QuestLogWidgetController;
	
}

void AFrozenHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass,TEXT("Overlay Widget Class UnInitialized please Fill Aura HUD"));
	checkf(OverlayWidgetControllerClass,TEXT("Overlay Widget Controller Class UnInitialized please Fill Aura HUD"));
	
	
	
	//Overlay Widget Creation
	UUserWidget* Widget = CreateWidget<UFrozenUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UFrozenUserWidget>(Widget);
	
	//Overlay Widget Controller Setting Up 
	const FWidgetControllerParameters FWidgetControllerParameters(PC,PS,ASC,AS);
	UOverlayWidgetController * InOverlayWidgetController = GetOverlayWidgetController(FWidgetControllerParameters); 
	
	// Connect Both Overlay Widget & OverlayWidget Controller 
	
	OverlayWidget->SetWidgetController(InOverlayWidgetController);
	InOverlayWidgetController->BroadcastInitialValues();
	
	OverlayWidget->AddToViewport();
}


