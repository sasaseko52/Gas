// Copyright Mostafa Ibrahem

#include "FrozenAssetManager.h"
#include "FrozenGameplayTags.h"

UFrozenAssetManager& UFrozenAssetManager::Get()
{
	check(GEngine);
	UFrozenAssetManager* FrozenAssetManager = Cast<UFrozenAssetManager>(GEngine->AssetManager);
	return *FrozenAssetManager;
}

void UFrozenAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	
	FFrozenGameplayTags::InitializeNativeGameplayTags();
}
