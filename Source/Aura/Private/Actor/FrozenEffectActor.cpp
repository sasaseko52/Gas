// Copyright Mostafa Ibrahem


#include "Actor/FrozenEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"



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
	FGameplayEffectSpecHandle EffectSpecHandle = TargetAbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass,ActorLevel,EffectContextHandle);
	FActiveGameplayEffectHandle ActiveEffectHandle= TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	
	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bIsInfinite && InfiniteRemovalApplicationPolicy == EEffectRemovalApplicationPolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(ActiveEffectHandle,TargetAbilitySystemComponent);
	}
}

void AFrozenEffectActor::OnOverlap(AActor* TargetActor)
{
	
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,InfiniteGameplayEffectClass);
	}
}

void AFrozenEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
			ApplyEffectToTarget(TargetActor,InfiniteGameplayEffectClass);
	}
	if (InfiniteRemovalApplicationPolicy == EEffectRemovalApplicationPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetASC)) return;
		
		TargetASC->RemoveActiveGameplayEffectBySourceEffect(InfiniteGameplayEffectClass,TargetASC,1);
				
	}
}



