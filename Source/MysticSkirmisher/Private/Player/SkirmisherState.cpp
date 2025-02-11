// Copyright David-6


#include "Player/SkirmisherState.h"
#include "AbilitySystem/SkirmisherAbilitySystemComponent.h"
#include "AbilitySystem/SkirmisherAttributeSet.h"
#include "Net/UnrealNetwork.h"



ASkirmisherState::ASkirmisherState()
{
    SetNetUpdateFrequency(100.f);

    AbilitySystemComponent = CreateDefaultSubobject<USkirmisherAbilitySystemComponent>("AbilitySystemComponent");
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
    AttributeSet = CreateDefaultSubobject<USkirmisherAttributeSet>("AttributeSet");
}

void ASkirmisherState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ASkirmisherState, Level);
}

UAbilitySystemComponent *ASkirmisherState::GetAbilitySystemComponent() const    
{
    return AbilitySystemComponent;
}
void ASkirmisherState::OnRep_Level(int32 PrevLevel)
{

}
