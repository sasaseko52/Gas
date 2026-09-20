// Copyright Mostafa Ibrahem


#include "Character/MainCharacterBase.h"



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

