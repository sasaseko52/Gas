// Copyright Mostafa Ibrahem


#include "Character/MainCharacterBase.h"



AMainCharacterBase::AMainCharacterBase()
{
 	PrimaryActorTick.bCanEverTick = false;
	
	Weapon  = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(),FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}

// Called when the game starts or when spawned
void AMainCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

