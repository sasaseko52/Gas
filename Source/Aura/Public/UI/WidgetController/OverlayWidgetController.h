// Copyright Mostafa Ibrahem

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/FrozenWidgetController.h"
#include "OverlayWidgetController.generated.h"


UCLASS()
class AURA_API UOverlayWidgetController : public UFrozenWidgetController
{
	GENERATED_BODY()
public:
	
	virtual void BroadcastInitialValues()override;
};
