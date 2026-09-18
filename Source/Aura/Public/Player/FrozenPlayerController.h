// Copyright Mostafa Ibrahem

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FrozenPlayerController.generated.h"

class UInputMappingContext;
UCLASS()
class AURA_API AFrozenPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AFrozenPlayerController();
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> FrozenContext;
};
