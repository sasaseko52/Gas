// Copyright Mostafa Ibrahem


#include "UI/HUD/FrozenHUD.h"
#include "UI/Widget/FrozenUserWidget.h"
#include "Blueprint/UserWidget.h"



void AFrozenHUD::BeginPlay()
{
	Super::BeginPlay();
	
	UUserWidget* Widget = CreateWidget<UFrozenUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}
