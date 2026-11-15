// Copyright Mostafa Ibrahem

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DamageTextComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UDamageTextComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
	
	
	
	
	
public:
	
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void SetDamageEvent(float Damage);
};
