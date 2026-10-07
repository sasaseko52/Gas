// Copyright Mostafa Ibrahem

#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UI/WidgetController/FrozenWidgetController.h"
#include "OverlayWidgetController.generated.h"

class UFrozenUserWidget;
struct FOnAttributeChangeData;
USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag AssetTag = FGameplayTag();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Message = FText();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UFrozenUserWidget> MessageWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Image = nullptr;
	
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMessageWidgetRowSignature,FUIWidgetRow,UIWidgetRow);


UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UFrozenWidgetController
{
	GENERATED_BODY()
public:
	
	virtual void BroadcastInitialValues()override;
	virtual void BindCallbacksToDependencies() override;
	
	
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChangedDelegate;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChangedDelegate;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnManaChangedDelegate;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMaxManaChangedDelegate;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMessageWidgetRowSignature MessageWidgetRowDelegate;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "WidgetData")
	TObjectPtr<UDataTable> MessageWidgetDataTable;
	
	
	//Functions Bound to OnAttributeChangeDelegate
	void HealthChanged(const FOnAttributeChangeData& Data);
	void MaxHealthChanged(const FOnAttributeChangeData& Data);
	void ManaChanged(const FOnAttributeChangeData& Data);
	void MaxManaChanged(const FOnAttributeChangeData& Data);
	void TagContainerChanged(const FGameplayTagContainer& TagContainer);
	
	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);
	
	
	
};

template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(),TEXT(""));
	
}
