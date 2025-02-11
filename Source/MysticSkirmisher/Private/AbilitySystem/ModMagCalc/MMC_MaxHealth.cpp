// Copyright David-6


#include "AbilitySystem/ModMagCalc/MMC_MaxHealth.h"
#include "AbilitySystem/SkirmisherAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
    VigorDef.AttributeToCapture = USkirmisherAttributeSet::GetVigorAttribute();
    VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    VigorDef.bSnapshot = false;

    RelevantAttributesToCapture.Add(VigorDef);


    
    StrengthDef.AttributeToCapture = USkirmisherAttributeSet::GetStrengthAttribute();
    StrengthDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    StrengthDef.bSnapshot = false;
    RelevantAttributesToCapture.Add(StrengthDef);

}
float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec &Spec) const
{
    // Gather tags from source and target

    const FGameplayTagContainer* sourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* targetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    FAggregatorEvaluateParameters evaluateParameters;
    evaluateParameters.SourceTags = sourceTags;
    evaluateParameters.TargetTags = targetTags;

    float vigor = 0.f;
    float strength = 0.f;

    GetCapturedAttributeMagnitude(VigorDef, Spec, evaluateParameters, vigor);
    GetCapturedAttributeMagnitude(StrengthDef, Spec, evaluateParameters, strength);


    vigor = FMath::Max<float>(vigor, 0.f);
    strength = FMath::Max<float>(strength, 0.f);
    
    ICombatInterface* combatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
    const int32 playerLevel = combatInterface->GetCurrentLevel();
    
    float calcVigor = 1.5f * vigor;
    float calcStrength = 0.2f * strength;
    
    // 5 + vigor(3) * 1.2 + strength(6) * 2.5 + level(1)
    
    return (playerLevel + calcVigor) * calcStrength;
}