// Copyright Mostafa Ibrahem

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "FrozenPlayerState.generated.h"

class UQuestManagerComponent;
class UAbilitySystemComponent;
class UAttributeSet;
UCLASS()
class AURA_API AFrozenPlayerState : public APlayerState , public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	
	AFrozenPlayerState();
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	//Getters
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const;
	UQuestManagerComponent* GetQuestManagerComponent() const;
	FORCEINLINE int32 GetPlayerLevel() const {return Level;}
	
	
	
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
	TObjectPtr<UQuestManagerComponent> QuestManagerComponent;
private:
	
	UPROPERTY(ReplicatedUsing= OnRep_Level,VisibleAnywhere)
	int32 Level = 1;
	
	UFUNCTION()
	void OnRep_Level(int32 OldLevel);
};
