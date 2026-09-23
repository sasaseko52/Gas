// Copyright Mostafa Ibrahem


#include "Actor/FrozenEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/FrozenAttributeSet.h"
#include "Components/SphereComponent.h"


AFrozenEffectActor::AFrozenEffectActor()
{
 	
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(Mesh);
	

}

void AFrozenEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UFrozenAttributeSet* FrozenAttributeSet =Cast<UFrozenAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UFrozenAttributeSet::StaticClass()));
		UFrozenAttributeSet* MutableFrozenAttributeSet = const_cast<UFrozenAttributeSet*>(FrozenAttributeSet);
		MutableFrozenAttributeSet->SetHealth(FrozenAttributeSet->GetHealth()+25.f);
		Destroy();
	}
}

void AFrozenEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void AFrozenEffectActor::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this,&AFrozenEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this,&AFrozenEffectActor::OnEndOverlap);
}



