// Copyright David-6


#include "AbilitySystem/SkirmisherAttributeSet.h"
#include "Net/UnrealNetwork.h"

USkirmisherAttributeSet::USkirmisherAttributeSet()
{
    InitHealth(20.f);
    InitHealthMax(60.f);
    InitMana(10.f);
    InitManaMax(40.f);
}

void USkirmisherAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION_NOTIFY(USkirmisherAttributeSet, Health, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(USkirmisherAttributeSet, HealthMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(USkirmisherAttributeSet, Mana, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(USkirmisherAttributeSet, ManaMax, COND_None, REPNOTIFY_Always);
}
void USkirmisherAttributeSet::OnRep_Health(const FGameplayAttributeData& PrevHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USkirmisherAttributeSet, Health, PrevHealth);
}

void USkirmisherAttributeSet::OnRep_HealthMax(const FGameplayAttributeData &PrevHealthMax) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USkirmisherAttributeSet, HealthMax, PrevHealthMax);
}

void USkirmisherAttributeSet::OnRep_Mana(const FGameplayAttributeData &PrevMana) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USkirmisherAttributeSet, Mana, PrevMana);
}

void USkirmisherAttributeSet::OnRep_ManaMax(const FGameplayAttributeData & PrevManaMax) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USkirmisherAttributeSet, ManaMax, PrevManaMax);
}
