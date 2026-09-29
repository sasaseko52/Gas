// Copyright Mostafa Ibrahem

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FrozenEffectActor.generated.h"

class UGameplayEffect;
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
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category= "Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
	
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* Target,TSubclassOf<UGameplayEffect> GameplayEffectClass);
private:
	

};
