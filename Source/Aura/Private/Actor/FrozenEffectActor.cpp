// Copyright Mostafa Ibrahem


#include "Actor/FrozenEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"


AFrozenEffectActor::AFrozenEffectActor()
{
 	
	PrimaryActorTick.bCanEverTick = false;
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(FName("RootSceneComponent")));
}


void AFrozenEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFrozenEffectActor::ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	
	UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	if (TargetAbilitySystemComponent == nullptr) return;
	check(GameplayEffectClass);
	FGameplayEffectContextHandle  EffectContextHandle =TargetAbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this); 
	FGameplayEffectSpecHandle EffectSpecHandle = TargetAbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass,1.f,EffectContextHandle);
	TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	
}



