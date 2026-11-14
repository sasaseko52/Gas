// Copyright Mostafa Ibrahem


#include "Character/EnemyCharacter.h"

#include "FrozenGameplayTags.h"
#include "AbilitySystem/FrozenAbilitySystemComponent.h"
#include "AbilitySystem/FrozenAbilitySystemLibrary.h"
#include "AbilitySystem/FrozenAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/Widget/FrozenUserWidget.h"

AEnemyCharacter::AEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
	AbilitySystemComponent = CreateDefaultSubobject<UFrozenAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UFrozenAttributeSet>("AttributeSet");
	
	
	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
}

int32 AEnemyCharacter::GetPlayerLevel()
{
	return EnemyLevel;
}

void AEnemyCharacter::Die()
{
	SetLifeSpan(5.0f);
	Super::Die();
}


void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseSpeed;
	
	InitAbilityActorInfo();
	InitializeDefaultAttributes();
	
	UFrozenAbilitySystemLibrary::GiveStartupAbilities(this,AbilitySystemComponent);
	
	if (UFrozenUserWidget* FrozenUserWidget = Cast<UFrozenUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		FrozenUserWidget->SetWidgetController(this);
	}
	
	
	if (const UFrozenAttributeSet* FrozenAttributeSet = CastChecked<UFrozenAttributeSet>(AttributeSet))
	{
		//Broadcast the Future changes values of Health and Max Health
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(FrozenAttributeSet->GetHealthAttribute()).AddUObject(this,&AEnemyCharacter::OnHealthChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(FrozenAttributeSet->GetMaxHealthAttribute()).AddUObject(this,&AEnemyCharacter::OnMaxHealthChanged);
		
		//Broadcast the initial Values of Health and Max Health
		OnHealthChangedDelegate.Broadcast(FrozenAttributeSet->GetHealth());
		OnMaxHealthChangedDelegate.Broadcast(FrozenAttributeSet->GetMaxHealth());
		
		FFrozenGameplayTags GameplayTag = FFrozenGameplayTags::Get();
		AbilitySystemComponent->RegisterGameplayTagEvent(GameplayTag.Effects_HitReact).AddUObject(this,&AEnemyCharacter::OnHitReactTagChanged);
	}
	
}

void AEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	Cast<UFrozenAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	
	InitializeDefaultAttributes();
}


void AEnemyCharacter::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	OnHealthChangedDelegate.Broadcast(Data.NewValue);
}

void AEnemyCharacter::OnMaxHealthChanged(const FOnAttributeChangeData& Data)
{
	OnMaxHealthChangedDelegate.Broadcast(Data.NewValue);
}

void AEnemyCharacter::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(250);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(250);
}

void AEnemyCharacter::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

void AEnemyCharacter::OnHitReactTagChanged(const FGameplayTag Tag, int32 TagCount)
{
	 bHitReact = TagCount > 0;
	
	
	GetCharacterMovement()->MaxWalkSpeed = bHitReact ? 0 : BaseSpeed;
		

		
		
		
}