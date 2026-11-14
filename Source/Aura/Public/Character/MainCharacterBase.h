// Copyright Mostafa Ibrahem

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "MainCharacterBase.generated.h"

class UGameplayAbility;
class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;
class UAnimMontage;

UCLASS(Abstract)
class AURA_API AMainCharacterBase : public ACharacter, public IAbilitySystemInterface , public ICombatInterface
{
	GENERATED_BODY()

public:
	
	AMainCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const;
	
	
	//Combat Interface
	virtual UAnimMontage* GetHitReactAnimation_Implementation() override;
	
	virtual void Die() override;
	//virtual int32 GetPlayerLevel()  override;
	
	
	
	UFUNCTION(NetMulticast,Reliable)
	virtual void MulticastHandleDeath();
protected:
	
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo();
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
	
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	FName WeaponTipSocketName;
	
	
	virtual FVector GetCombatSocketLocation() override;
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
	
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;
	
	
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass,float Level);
	
	virtual void InitializeDefaultAttributes();
	
	void AddCharacterAbilities();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults" , meta = (AllowPrivateAccess = true))
	ECharacterClass CharacterClass = ECharacterClass::Knight;
private:
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;
};
