// Copyright David-6


#include "AbilitySystem/SkirmisherAbilitySystemComponent.h"
#include "SkirmisherGameplayTags.h"

void USkirmisherAbilitySystemComponent::AbilityActorInfoSet()
{
    OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &USkirmisherAbilitySystemComponent::EffectApplied);
}

void USkirmisherAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>> &StartupAbilities)
{
    for (TSubclassOf<UGameplayAbility> abilityClass : StartupAbilities)
    {
        FGameplayAbilitySpec abilitySpec = FGameplayAbilitySpec(abilityClass, 1);
        //GiveAbility(abilitySpec);
        GiveAbilityAndActivateOnce(abilitySpec);
    }
}
void USkirmisherAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
    FGameplayTagContainer tagContainer;
    EffectSpec.GetAllAssetTags(tagContainer);
    EffectAssetTags.Broadcast(tagContainer);
}