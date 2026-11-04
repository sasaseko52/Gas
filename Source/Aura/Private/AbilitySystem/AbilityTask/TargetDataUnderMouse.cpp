// Copyright Mostafa Ibrahem


#include "AbilitySystem/AbilityTask/TargetDataUnderMouse.h"
#include "AbilitySystemComponent.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* TargetDataAbilityTask = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	
	
	
	return TargetDataAbilityTask;
}

void UTargetDataUnderMouse::Activate()
{
	
	if (Ability->GetCurrentActorInfo()->IsLocallyControlled())
	{
		SendMouseCursorData();
	}
	else
	{
		//Delegate receives the  target data from client and keep it Cached to be broadcasted
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(GetAbilitySpecHandle(),GetActivationPredictionKey()).AddUObject(this,&UTargetDataUnderMouse::OnTargetDataReplicatedCallBack);
		bool  bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(GetAbilitySpecHandle(),GetActivationPredictionKey());
		if (!bCalledDelegate)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
		
	
	
	
	
}

void UTargetDataUnderMouse::SendMouseCursorData()
{
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());
	
	FHitResult Hit;
	Ability->GetCurrentActorInfo()->PlayerController->GetHitResultUnderCursor(ECC_Visibility,false,Hit);
	
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult = Hit;
	FGameplayAbilityTargetDataHandle TargetDataHandle;
	TargetDataHandle.Add(Data);
	//Replicate the target Data from client to server
	AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(),
			GetActivationPredictionKey(),
			TargetDataHandle,
			FGameplayTag(),
			AbilitySystemComponent->ScopedPredictionKey);
	
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		//send data to the ability to be used
		TargetDataDelegate.Broadcast(TargetDataHandle);
	}
}

void UTargetDataUnderMouse::OnTargetDataReplicatedCallBack(const FGameplayAbilityTargetDataHandle& DataHandle,
	FGameplayTag ActivationTag)
{
	//Target Data is Received , don't keep cached anymore
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(),GetActivationPredictionKey());
	
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		//send data to the ability to be used
		TargetDataDelegate.Broadcast(DataHandle);
	}
	
}
