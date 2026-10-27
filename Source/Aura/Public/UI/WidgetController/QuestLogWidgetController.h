// Copyright Mostafa Ibrahem

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/FrozenWidgetController.h"
#include "AbilitySystem/Data/QuestCollectionInfo.h"
#include "QuestLogWidgetController.generated.h"


class UQuestManagerComponent;
struct FFrozenQuestRowData;
class UQuestInfo;
struct FFrozenQuestInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestRowsUpdated,const TArray<FFrozenCollectionInfo>&,QuestRows);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCollectionSelected,const FGameplayTag& ,CollectionTag, const TArray<FFrozenQuestRowData>&, Rows);

UCLASS(BlueprintType, Blueprintable)
class AURA_API UQuestLogWidgetController : public UFrozenWidgetController
{
	GENERATED_BODY()
public:
	virtual void BindCallbacksToDependencies() override;	
	virtual void BroadcastInitialValues() override;
	
	UFUNCTION(BlueprintCallable, Category="GAS|QuestInfo")
	void SelectCollection(const FGameplayTag& CollectionTag);
	
	
	UPROPERTY(BlueprintAssignable,Category="GAS|AttributeInfo")
	FOnQuestRowsUpdated FrozenQuestRowsDelegate;
	
	UPROPERTY(BlueprintAssignable,Category="GAS|AttributeInfo")
	FOnCollectionSelected QuestCollectionSelectedDelegate;
	
protected:
	
	UPROPERTY(EditDefaultsOnly,Category="GAS|QuestInfo")
	TObjectPtr<UQuestInfo> QuestInfo;
	

	
	
private:
	
	TObjectPtr<UQuestManagerComponent> GetQuestManagerComponent();
};
