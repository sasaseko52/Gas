// Copyright Mostafa Ibrahem

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FrozenProjectile.generated.h"
class UNiagaraSystem;
class USphereComponent;
class UProjectileMovementComponent;
UCLASS()
class AURA_API AFrozenProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AFrozenProjectile();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
protected:

	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor ,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult);
	
private:
	
	UPROPERTY(EditDefaultsOnly)
	float LifeSpan = 15.f;
	
	bool bHit = false;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> ImpactEffect;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ImpactSound;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> LoopingSound;
	
	UPROPERTY()
	TObjectPtr<UAudioComponent> LoopingCompnent;
};
