// Copyright Mostafa Ibrahem

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FrozenHUD.generated.h"

class UFrozenUserWidget;
UCLASS()
class AURA_API AFrozenHUD : public AHUD
{
	GENERATED_BODY()
public:
	
	UPROPERTY(BlueprintReadOnly, Category = "Widget")
	TObjectPtr<UFrozenUserWidget> OverlayWidget;
	
protected:
	
	virtual void BeginPlay() override;
	
private:
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UFrozenUserWidget> OverlayWidgetClass;
	
	
};
