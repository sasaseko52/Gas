// Copyright Mostafa Ibrahem

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FrozenGameMode.generated.h"

class UCharacterClassInfo;
/**
 * 
 */
UCLASS()
class AURA_API AFrozenGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	
public:
	
	UPROPERTY(EditDefaultsOnly, Category= "Character Class Info")
	TObjectPtr<UCharacterClassInfo> CharacterInfoClass;
	
	
	
};
