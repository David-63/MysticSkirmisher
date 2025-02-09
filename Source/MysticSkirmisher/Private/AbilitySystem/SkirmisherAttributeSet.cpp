// Copyright David-6


#include "AbilitySystem/SkirmisherAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/Character.h"

USkirmisherAttributeSet::USkirmisherAttributeSet()
{
    InitHealth(5.f);
    InitHealthMax(45.f);
    InitMana(5.f);
    InitManaMax(25.f);
}

void USkirmisherAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION_NOTIFY(USkirmisherAttributeSet, Health, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(USkirmisherAttributeSet, HealthMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(USkirmisherAttributeSet, Mana, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(USkirmisherAttributeSet, ManaMax, COND_None, REPNOTIFY_Always);

    DOREPLIFETIME_CONDITION_NOTIFY(USkirmisherAttributeSet, Strength, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(USkirmisherAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(USkirmisherAttributeSet, Resilience, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(USkirmisherAttributeSet, Vigor, COND_None, REPNOTIFY_Always);
    
}

void USkirmisherAttributeSet::PreAttributeChange(const FGameplayAttribute &Attribute, float &NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);

    if (Attribute == GetHealthAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.f, GetHealthMax());
    }
    if (Attribute == GetManaAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.f, GetManaMax());
    }
}

void USkirmisherAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData &Data, FEffectProperties &Props) const
{
    // Source = Causer of the effect, Target = Target of the effect (owner of this AS)

    Props.EffectContextHandle = Data.EffectSpec.GetContext();
    Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
    
    if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
    {
        Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
        Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
        if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
        {
            if (APawn* pawn = Cast<APawn>(Props.SourceAvatarActor))
            {
                Props.SourceController = pawn->GetController();
            }
        }
        if (Props.SourceController)
        {
            Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
        }
    }

    if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
    {
        Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
        Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
        Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
        Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);

    }
}

void USkirmisherAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData & Data)
{
    Super::PostGameplayEffectExecute(Data);

    FEffectProperties props;
    SetEffectProperties(Data, props);
    
    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        SetHealth(FMath::Clamp(GetHealth(), 0.f, GetHealthMax()));
    }
    if (Data.EvaluatedData.Attribute == GetManaAttribute())
    {
        SetMana(FMath::Clamp(GetMana(), 0.f, GetManaMax()));
    }
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

void USkirmisherAttributeSet::OnRep_Strength(const FGameplayAttributeData &PrevStrength) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USkirmisherAttributeSet, Strength, PrevStrength);

}
void USkirmisherAttributeSet::OnRep_Intelligence(const FGameplayAttributeData &PrevIntelligence) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USkirmisherAttributeSet, Intelligence, PrevIntelligence);
}

void USkirmisherAttributeSet::OnRep_Resilience(const FGameplayAttributeData &PrevResilience) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USkirmisherAttributeSet, Resilience, PrevResilience);
}

void USkirmisherAttributeSet::OnRep_Vigor(const FGameplayAttributeData &PrevVigor) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USkirmisherAttributeSet, Vigor, PrevVigor);
}
