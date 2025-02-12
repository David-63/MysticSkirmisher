// Copyright David-6


#include "AbilitySystem/SkirmisherAbilitySystemComponent.h"
#include "SkirmisherGameplayTags.h"

void USkirmisherAbilitySystemComponent::AbilityActorInfoSet()
{
    OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &USkirmisherAbilitySystemComponent::EffectApplied);

    const FSkirmisherGameplayTags& gameplayTags = FSkirmisherGameplayTags::Get();
    
    GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Orange, FString::Printf(TEXT("Tag: %s"), *gameplayTags.Attributes_Secondary_Armor.ToString()));
}

void USkirmisherAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
    FGameplayTagContainer tagContainer;
    EffectSpec.GetAllAssetTags(tagContainer);
    EffectAssetTags.Broadcast(tagContainer);
}