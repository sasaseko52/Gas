// Copyright Mostafa Ibrahem

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Character/MainCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "EnemyCharacter.generated.h"


class UWidgetComponent;

UCLASS()
class AURA_API AEnemyCharacter : public AMainCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	
public:
	AEnemyCharacter();
	

	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	
	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted;
	
	//Combat Interface
	virtual int32 GetPlayerLevel() override;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChangedDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChangedDelegate;
	
	void OnHitReactTagChanged(const FGameplayTag Tag, int32 TagCount);
	
	UPROPERTY(BlueprintReadOnly, Category= "Combat")
	bool bHitReact = false;
	UPROPERTY(BlueprintReadOnly, Category= "Combat")
	float BaseSpeed = 250.f;
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults" , meta = (AllowPrivateAccess = true))
	int32 EnemyLevel = 1;
	
	
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;
	
	
	void OnHealthChanged(const FOnAttributeChangeData& Data);
	void OnMaxHealthChanged(const FOnAttributeChangeData& Data);
	
private:
	
	
};
