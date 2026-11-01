// Copyright Mostafa Ibrahem

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "FrozenPlayerController.generated.h"

class UFrozenAbilitySystemComponent;
class UFrozenInputConfig;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;
class USplineComponent;

UCLASS()
class AURA_API AFrozenPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AFrozenPlayerController();
	void AutoRun();
	virtual void PlayerTick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> FrozenContext;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	
	void Move(const FInputActionValue& InputActionValue);
	void CursorTrace();
	FHitResult CursorHit;
	
	TScriptInterface<IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> ThisActor;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UFrozenInputConfig> FrozenInputConfig;
	
	
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
	
	UPROPERTY()
	TObjectPtr<UFrozenAbilitySystemComponent> FrozenAbilitySystemComponent;
	
	UFrozenAbilitySystemComponent* GetASC();
	
	//  Click  To Move 
	
	
	FVector CachedDestination =  FVector::ZeroVector;
	//Time the player follow the cursor
	float  FollowTime = 0.0f;
	
	// Hold Time Threshold to determine either move to location(short press) or (Long Press Hold) follow the cursor
	float ShortPressThreshold = 0.5f;
	
	bool bAutoRunning = false;
	bool bTargeting = false;
	
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;
	
	
};
