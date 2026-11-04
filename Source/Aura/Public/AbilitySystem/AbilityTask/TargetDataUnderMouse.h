// Copyright Mostafa Ibrahem

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderMouse.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetDataSignature,const FGameplayAbilityTargetDataHandle&,DataHandle);
UCLASS()
class AURA_API UTargetDataUnderMouse : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	
	
	UPROPERTY(BlueprintAssignable,Category="Ability|Tasks")
	FMouseTargetDataSignature TargetDataDelegate;
	
	UFUNCTION(BlueprintCallable,Category = "Ability|Tasks",meta = (DisplayName = "TargetDataUnderMouse",HidePin = "OwningAbility",DefaultToSelf = "OwningAbility",BlueprintInternalUseOnly = "true"))
	static UTargetDataUnderMouse* CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility);
	
	
private:
	
	virtual void Activate() override;
	
	void SendMouseCursorData();
	
	
	void OnTargetDataReplicatedCallBack(const FGameplayAbilityTargetDataHandle& DataHandle,FGameplayTag ActivationTag);
};
