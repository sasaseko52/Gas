// Copyright Mostafa Ibrahem

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/FrozenWidgetController.h"
#include "QuestLogWidgetController.generated.h"

class UQuestInfo;
struct FFrozenQuestInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FrozenQuestInfoSignature,const FFrozenQuestInfo&,QuestInfo);
UCLASS(BlueprintType, Blueprintable)
class AURA_API UQuestLogWidgetController : public UFrozenWidgetController
{
	GENERATED_BODY()
public:
	virtual void BindCallbacksToDependencies() override;	
	virtual void BroadcastInitialValues() override;
	
	UPROPERTY(BlueprintAssignable,Category="GAS|AttributeInfo")
	FrozenQuestInfoSignature FrozenQuestInfoDelegate;
	
	protected:
	
	UPROPERTY(EditDefaultsOnly,Category="GAS|QuestInfo")
	TObjectPtr<UQuestInfo> QuestInfo;
};
