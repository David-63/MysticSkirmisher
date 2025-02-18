// Copyright David-6


#include "AbilitySystem/SkirmisherAbilitySystemComponent.h"
#include "SkirmisherGameplayTags.h"
#include "AbilitySystem/SkirmisherGameplayAbility.h"

void USkirmisherAbilitySystemComponent::AbilityActorInfoSet()
{
    OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &USkirmisherAbilitySystemComponent::ClientEffectApplied);
}

void USkirmisherAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>> &StartupAbilities)
{
    for (const TSubclassOf<UGameplayAbility> abilityClass : StartupAbilities)
    {
        FGameplayAbilitySpec abilitySpec = FGameplayAbilitySpec(abilityClass, 1);
        if (const USkirmisherGameplayAbility* skirmisherAbility = Cast<USkirmisherGameplayAbility>(abilitySpec.Ability) )
        {
            abilitySpec.GetDynamicSpecSourceTags().AddTag(skirmisherAbility->StartupInputTag);
            GiveAbility(abilitySpec);
        }        
    }
}

void USkirmisherAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
    if (!InputTag.IsValid()) return;
    
    for (auto& abilitySpec : GetActivatableAbilities())
    {
        if (abilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
        {
            AbilitySpecInputReleased(abilitySpec);            
        }
    }
}
void USkirmisherAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
    if (!InputTag.IsValid()) return;
    
    for (auto& abilitySpec : GetActivatableAbilities())
    {
        if (abilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
        {
            AbilitySpecInputPressed(abilitySpec);
            if (!abilitySpec.IsActive())
            {
                TryActivateAbility(abilitySpec.Handle);
            }
        }
    }
}


void USkirmisherAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
    FGameplayTagContainer tagContainer;
    EffectSpec.GetAllAssetTags(tagContainer);
    EffectAssetTags.Broadcast(tagContainer);
}