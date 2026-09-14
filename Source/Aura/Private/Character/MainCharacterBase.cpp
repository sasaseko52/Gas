// Copyright Mostafa Ibrahem


#include "Character/MainCharacterBase.h"

#include "Kismet/GameplayStatics.h"


AMainCharacterBase::AMainCharacterBase()
{
 	PrimaryActorTick.bCanEverTick = false;
	
	
}

// Called when the game starts or when spawned
void AMainCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

