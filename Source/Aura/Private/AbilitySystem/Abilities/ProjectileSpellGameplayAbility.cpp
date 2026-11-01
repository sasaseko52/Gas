// Copyright Mostafa Ibrahem


#include "AbilitySystem/Abilities/ProjectileSpellGameplayAbility.h"
#include "Actor/FrozenProjectile.h"
#include "Interaction/CombatInterface.h"


void UProjectileSpellGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                      const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                      const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	
	 if (!HasAuthority(&ActivationInfo)) return;
	 
	
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	
	if (CombatInterface)
	{
		FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		
		AFrozenProjectile* Projectile = GetWorld()->SpawnActorDeferred<AFrozenProjectile>(ProjectileClass,SpawnTransform,GetOwningActorFromActorInfo(),
				GetOwningActorFromActorInfo()->GetInstigator(),ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		
		
		
		
		
		Projectile->FinishSpawning(SpawnTransform);
	}
	
	
	
	
	
	
	
	
	
	
	
}
