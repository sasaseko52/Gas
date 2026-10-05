// Copyright Mostafa Ibrahem


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/FrozenAbilitySystemComponent.h"
#include "AbilitySystem/FrozenAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UFrozenAttributeSet* FrozenAttributeSet = CastChecked<UFrozenAttributeSet>(AttributeSet);
	//Broadcast the initial Values
	OnHealthChangedDelegate.Broadcast(FrozenAttributeSet->GetHealth());
	OnMaxHealthChangedDelegate.Broadcast(FrozenAttributeSet->GetMaxHealth());
	OnManaChangedDelegate.Broadcast(FrozenAttributeSet->GetMana());
	OnMaxManaChangedDelegate.Broadcast(FrozenAttributeSet->GetMaxMana());


}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UFrozenAttributeSet* FrozenAttributeSet = CastChecked<UFrozenAttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(FrozenAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(FrozenAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(FrozenAttributeSet->GetManaAttribute()).AddUObject(this,&UOverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(FrozenAttributeSet->GetMaxManaAttribute()).AddUObject(this,&UOverlayWidgetController::MaxManaChanged);
	Cast<UFrozenAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTagsDelegate.AddUObject(this, &UOverlayWidgetController::TagContainerChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data)
{
	OnHealthChangedDelegate.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	OnMaxHealthChangedDelegate.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data)
{
	OnManaChangedDelegate.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data)
{
	OnMaxManaChangedDelegate.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::TagContainerChanged(const FGameplayTagContainer& TagContainer)
{
	for (const FGameplayTag& Tag : TagContainer)
	{
		FUIWidgetRow* WidgetRow = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable,Tag);
		WidgetRow->Message;
		GEngine->AddOnScreenDebugMessage(-1,3,FColor::Green,FString::Printf(TEXT("TagContainerChanged,%s"),*WidgetRow->Message.ToString()));
	}
}
