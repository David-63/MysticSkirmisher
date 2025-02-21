// Copyright David-6


#include "AbilitySystem/Abilities/SkirmisherProjectileSpell.h"
#include "Actor/SkirmisherProjectile.h"
#include "Interaction/CombatInterface.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


void USkirmisherProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData * TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    
}

void USkirmisherProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
    
    const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();

    if (!bIsServer) return;

    check(ProjectileClass);
    
    ICombatInterface* combatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
    if (combatInterface)
    {
        const FVector socketLocation = combatInterface->GetCombatSocketLocation();
        FRotator rotation = (ProjectileTargetLocation - socketLocation).Rotation();
        rotation.Pitch = 0.f;

        FTransform spawnTransform;
        spawnTransform.SetLocation(socketLocation);
        spawnTransform.SetRotation(rotation.Quaternion());

        ASkirmisherProjectile* projectile = GetWorld()->SpawnActorDeferred<ASkirmisherProjectile>
        (
            ProjectileClass, spawnTransform, GetOwningActorFromActorInfo()
            , Cast<APawn>(GetOwningActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn
        );
        
        const UAbilitySystemComponent* sourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
        const FGameplayEffectSpecHandle specHandle = sourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), sourceASC->MakeEffectContext());
        projectile->DamageEffectSpecHandle = specHandle;

        projectile->FinishSpawning(spawnTransform);
    }
}