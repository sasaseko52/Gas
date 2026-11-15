// Copyright Mostafa Ibrahem


#include "Character/MainCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/FrozenAbilitySystemComponent.h"
#include "AbilitySystem/FrozenAbilitySystemLibrary.h"
#include "Aura/Aura.h"
#include "Components/CapsuleComponent.h"



AMainCharacterBase::AMainCharacterBase()
{
 	PrimaryActorTick.bCanEverTick = false;
	
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile,ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);
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

UAnimMontage* AMainCharacterBase::GetHitReactAnimation_Implementation()
{
	return HitReactMontage;
}

void AMainCharacterBase::Die()
{
	//if (!HasAuthority())return;
	
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld,true));
	MulticastHandleDeath();
	
	
	
}

void AMainCharacterBase::MulticastHandleDeath_Implementation()
{
	if (Weapon)
	{
		Weapon->SetSimulatePhysics(true);
		Weapon->SetEnableGravity(true);
		Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	}
	
	
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Block);
	
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Dissolve();
}


// Called when the game starts or when spawned
void AMainCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMainCharacterBase::InitAbilityActorInfo()
{
}

FVector AMainCharacterBase::GetCombatSocketLocation()
{
	if (!Weapon) return FVector();
	return Weapon->GetSocketLocation(WeaponTipSocketName);
	
}

void AMainCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level)
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	FGameplayEffectContextHandle ContextHandle =GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const  FGameplayEffectSpecHandle EffectSpec =GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass,Level,ContextHandle);
	
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpec.Data.Get(),GetAbilitySystemComponent());
}

void AMainCharacterBase::InitializeDefaultAttributes()
{
	UFrozenAbilitySystemLibrary::InitializeDefaultAttributes(AbilitySystemComponent,this,CharacterClass,GetPlayerLevel());
}

void AMainCharacterBase::AddCharacterAbilities()
{
	UFrozenAbilitySystemComponent* FrozenASC = Cast<UFrozenAbilitySystemComponent>(GetAbilitySystemComponent());
	if (!HasAuthority())return;
	
	FrozenASC->AddCharacterAbilities(StartupAbilities);
	
}

void AMainCharacterBase::Dissolve()
{
	if (IsValid(DissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMatInstance = UMaterialInstanceDynamic::Create(DissolveMaterialInstance,this);
		GetMesh()->SetMaterial(0,DynamicMatInstance);
		
		StartDissolveTimeline(DynamicMatInstance);
	}
	if (IsValid(WeaponDissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMatInstance = UMaterialInstanceDynamic::Create(WeaponDissolveMaterialInstance,this);
		Weapon->SetMaterial(0,DynamicMatInstance);
		StartDissolveTimeline(DynamicMatInstance);
	}
}






