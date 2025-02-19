// Copyright David-6


#include "AbilitySystem/Abilities/SkirmisherProjectileSpell.h"
#include "Actor/SkirmisherProjectile.h"
#include "Interaction/CombatInterface.h"

void USkirmisherProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData * TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    
}

void USkirmisherProjectileSpell::SpawnProjectile()
{
    
    const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();

    if (!bIsServer) return;

    check(ProjectileClass);
    
    ICombatInterface* combatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
    if (combatInterface)
    {
        const FVector socketLocation = combatInterface->GetCombatSocketLocation();
        FTransform spawnTransform;
        spawnTransform.SetLocation(socketLocation);

        ASkirmisherProjectile* projectile = GetWorld()->SpawnActorDeferred<ASkirmisherProjectile>
        (
            ProjectileClass, spawnTransform, GetOwningActorFromActorInfo()
            , Cast<APawn>(GetOwningActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn
        );
        
        projectile->FinishSpawning(spawnTransform);
    }
}