// Copyright Mostafa Ibrahem

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "FrozenEffectActor.generated.h"

class UGameplayEffect;
class UAbilitySystemComponent;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};
UENUM(BlueprintType)
enum class EEffectRemovalApplicationPolicy
{
	RemoveOnEndOverlap,
	DoNotRemove
};

UCLASS()
class AURA_API AFrozenEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AFrozenEffectActor();

	
protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly,EditAnywhere , Category= "Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere , Category= "Effects")
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category= "Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category= "Effects")
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category= "Effects")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass ;
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category= "Effects")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category= "Effects")
	EEffectRemovalApplicationPolicy InfiniteRemovalApplicationPolicy = EEffectRemovalApplicationPolicy::RemoveOnEndOverlap;
	
	UFUNCTION(BlueprintCallable) 
	void ApplyEffectToTarget(AActor* TargetActor,TSubclassOf<UGameplayEffect> GameplayEffectClass);
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category= "Effects")
	bool bDestroyOnEffectRemoval = false;
	
	UFUNCTION(BlueprintCallable) 
	void OnOverlap(AActor* TargetActor);
	 
	UFUNCTION(BlueprintCallable) 
	void OnEndOverlap(AActor* TargetActor);
	
	UPROPERTY()
	TMap<FActiveGameplayEffectHandle,UAbilitySystemComponent*> ActiveEffectHandles;
private:
	

};
