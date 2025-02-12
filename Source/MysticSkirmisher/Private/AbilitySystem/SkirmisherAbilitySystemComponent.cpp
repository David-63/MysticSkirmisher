// Copyright David-6


#include "AbilitySystem/SkirmisherAbilitySystemComponent.h"
#include "SkirmisherGameplayTags.h"

void USkirmisherAbilitySystemComponent::AbilityActorInfoSet()
{
    OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &USkirmisherAbilitySystemComponent::EffectApplied);
}

void USkirmisherAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
    FGameplayTagContainer tagContainer;
    EffectSpec.GetAllAssetTags(tagContainer);
    EffectAssetTags.Broadcast(tagContainer);
}