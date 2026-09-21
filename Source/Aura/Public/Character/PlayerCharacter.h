// Copyright Mostafa Ibrahem

#pragma once

#include "CoreMinimal.h"
#include "Character/MainCharacterBase.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API APlayerCharacter : public AMainCharacterBase
{
	GENERATED_BODY()
	
public:
	APlayerCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
private:
	
	void InitAbilityActorInfo();
	
};
