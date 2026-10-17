// Copyright Mostafa Ibrahem

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "FrozenAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UFrozenAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
	public:
	
	static UFrozenAssetManager& Get();
	
	virtual void StartInitialLoading() override;
	
};
