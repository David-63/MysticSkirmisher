// Copyright David-6


#include "AbilitySystem/SkirmisherAbilitySystemComponent.h"

void USkirmisherAbilitySystemComponent::AbilityActorInfoSet()
{
    OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &USkirmisherAbilitySystemComponent::EffectApplied);
}

void USkirmisherAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
    GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Cyan, FString("Effect Applied"));
}