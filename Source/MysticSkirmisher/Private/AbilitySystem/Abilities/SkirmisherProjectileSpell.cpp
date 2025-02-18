// Copyright David-6


#include "AbilitySystem/Abilities/SkirmisherProjectileSpell.h"
#include "Kismet/KismetSystemLibrary.h"


void USkirmisherProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData * TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    UKismetSystemLibrary::PrintString(this, FString("ActivateAbility by C++"), true, true, FLinearColor::Yellow, 1.f);
}