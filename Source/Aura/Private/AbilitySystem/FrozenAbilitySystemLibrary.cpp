// Copyright Mostafa Ibrahem


#include "AbilitySystem/FrozenAbilitySystemLibrary.h"
#include "AbilitySystem/FrozenAttributeSet.h"
#include "Game/FrozenGameMode.h"
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

void UFrozenAbilitySystemLibrary::InitializeDefaultAttributes(UAbilitySystemComponent* ASC, const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level)
{
	
	AFrozenGameMode* FrozenGameMode = Cast<AFrozenGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
		
	if (!FrozenGameMode) return;
	
	AActor* AvatarActor = ASC->GetAvatarActor();
	
	FCharacterClassDefaultInfo CharacterClassDefaultInfo = FrozenGameMode->CharacterInfoClass->GetClassDefaultInfo(CharacterClass);
	
	FGameplayEffectContextHandle PrimaryContextHandle = ASC->MakeEffectContext();
	FGameplayEffectSpecHandle PrimarySpecHandle=	ASC->MakeOutgoingSpec(CharacterClassDefaultInfo.PrimaryAttributes,Level,PrimaryContextHandle);
	PrimaryContextHandle.AddSourceObject(AvatarActor);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimarySpecHandle.Data.Get());
	
	
	FGameplayEffectContextHandle SecondaryContextHandle = ASC->MakeEffectContext();
	FGameplayEffectSpecHandle SecondarySpecHandle=	ASC->MakeOutgoingSpec( FrozenGameMode->CharacterInfoClass->SecondaryAttributes,Level,SecondaryContextHandle);
	SecondaryContextHandle.AddSourceObject(AvatarActor);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondarySpecHandle.Data.Get());
	
	FGameplayEffectContextHandle VitalContextHandle = ASC->MakeEffectContext();
	FGameplayEffectSpecHandle VitalSpecHandle=	ASC->MakeOutgoingSpec( FrozenGameMode->CharacterInfoClass->VitalAttributes,Level,VitalContextHandle);
	VitalContextHandle.AddSourceObject(AvatarActor);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalSpecHandle.Data.Get());
	
}
