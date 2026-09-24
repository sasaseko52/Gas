// Copyright Mostafa Ibrahem


#include "UI/Widget/FrozenUserWidget.h"

void UFrozenUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
