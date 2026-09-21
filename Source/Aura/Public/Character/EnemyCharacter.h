// Copyright Mostafa Ibrahem

#pragma once

#include "CoreMinimal.h"
#include "Character/MainCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AEnemyCharacter : public AMainCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	
public:
	AEnemyCharacter();
	

	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	
	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted;
protected:
	virtual void BeginPlay() override;
};
