// Copyright Mostafa Ibrahem


#include "AbilitySystem/FrozenAbilitySystemLibrary.h"
#include "AbilitySystem/FrozenAttributeSet.h"
#include "Kismet/GameplayStatics.h"
#include "Player/FrozenPlayerState.h"
#include "UI/HUD/FrozenHUD.h"
#include "UI/WidgetController/FrozenWidgetController.h"

UOverlayWidgetController* UFrozenAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject,0))
	{
		if (AFrozenHUD* FrozenHUD = Cast<AFrozenHUD>(PC->GetHUD()))
		{
			AFrozenPlayerState* PS = PC->GetPlayerState<AFrozenPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			
			const FWidgetControllerParameters WidgetControllerParameters(PC,PS,ASC,AS);
			
			return FrozenHUD->GetOverlayWidgetController(WidgetControllerParameters);
			
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* UFrozenAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject,0))
	{
		if (AFrozenHUD* FrozenHUD = Cast<AFrozenHUD>(PC->GetHUD()))
		{
			AFrozenPlayerState* PS = PC->GetPlayerState<AFrozenPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			
			const FWidgetControllerParameters WidgetControllerParameters(PC,PS,ASC,AS);
			
			return FrozenHUD->GetAttributeMenuWidgetController(WidgetControllerParameters);
			
		}
		
	}
	return nullptr;
}

UQuestLogWidgetController* UFrozenAbilitySystemLibrary::GetQuestLogWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject,0))
	{
		if (AFrozenHUD* FrozenHUD = Cast<AFrozenHUD>(PC->GetHUD()))
		{
			AFrozenPlayerState* PS = PC->GetPlayerState<AFrozenPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			
			const FWidgetControllerParameters WidgetControllerParameters(PC,PS,ASC,AS);
			
			return FrozenHUD->GetQuestLogWidgetController(WidgetControllerParameters);
			
		}
		
	}
	
	
	return nullptr;
}
