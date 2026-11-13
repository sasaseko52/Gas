// Copyright Mostafa Ibrahem

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Data/CharacterClassInfo.h"
#include "FrozenAbilitySystemLibrary.generated.h"


class UAbilitySystemComponent;
class UQuestLogWidgetController;
class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class AURA_API UFrozenAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	
public:
	
	UFUNCTION(BlueprintPure, Category = "FrozenAbilitySystemLibrary|Widget Controller")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);
	
	
	UFUNCTION(BlueprintPure, Category = "FrozenAbilitySystemLibrary|Widget Controller")
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "FrozenAbilitySystemLibrary|Widget Controller")
	static UQuestLogWidgetController* GetQuestLogWidgetController(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, Category = "FrozenAbilitySystemLibrary|Character Class Info")
	static void InitializeDefaultAttributes(UAbilitySystemComponent* ASC,const UObject* WorldContextObject,ECharacterClass CharacterClass,  float  Level);
};
