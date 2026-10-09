// Copyright Mostafa Ibrahem


#include "Character/MainCharacterBase.h"
#include "AbilitySystemComponent.h"


AMainCharacterBase::AMainCharacterBase()
{
 	PrimaryActorTick.bCanEverTick = false;
	
	Weapon  = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(),FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}

UAbilitySystemComponent* AMainCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AMainCharacterBase::GetAttributeSet() const
{
	return AttributeSet;
}

// Called when the game starts or when spawned
void AMainCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMainCharacterBase::InitAbilityActorInfo()
{
}

void AMainCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level)
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	const  FGameplayEffectContextHandle ContextHandle =GetAbilitySystemComponent()->MakeEffectContext();
	const  FGameplayEffectSpecHandle EffectSpec =GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass,Level,ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpec.Data.Get(),GetAbilitySystemComponent());
}

void AMainCharacterBase::InitializeDefaultDefaultAttributes()
{
	ApplyEffectToSelf(DefaultPrimaryAttributes,1);
	ApplyEffectToSelf(DefaultSecondaryAttributes,1);
}





