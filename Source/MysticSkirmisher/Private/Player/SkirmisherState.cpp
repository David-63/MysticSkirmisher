// Copyright David-6


#include "Player/SkirmisherState.h"
#include "AbilitySystem/SkirmisherAbilitySystemComponent.h"
#include "AbilitySystem/SkirmisherAttributeSet.h"


ASkirmisherState::ASkirmisherState()
{
    SetNetUpdateFrequency(100.f);

    AbilitySystemComponent = CreateDefaultSubobject<USkirmisherAbilitySystemComponent>("AbilitySystemComponent");
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
    AttributeSet = CreateDefaultSubobject<USkirmisherAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* ASkirmisherState::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}
