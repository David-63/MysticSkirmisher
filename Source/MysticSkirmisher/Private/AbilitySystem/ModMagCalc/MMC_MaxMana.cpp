// Copyright David-6


#include "AbilitySystem/ModMagCalc/MMC_MaxMana.h"
#include "AbilitySystem/SkirmisherAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
    VigorDef.AttributeToCapture = USkirmisherAttributeSet::GetVigorAttribute();
    VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    VigorDef.bSnapshot = false;
    RelevantAttributesToCapture.Add(VigorDef);

    IntelligenceDef.AttributeToCapture = USkirmisherAttributeSet::GetIntelligenceAttribute();
    IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    IntelligenceDef.bSnapshot = false;
    RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec &Spec) const
{
    // Gather tags from source and target

    const FGameplayTagContainer* sourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* targetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    FAggregatorEvaluateParameters evaluateParameters;
    evaluateParameters.SourceTags = sourceTags;
    evaluateParameters.TargetTags = targetTags;

    float vigor = 0.f;
    float intelligence = 0.f;

    GetCapturedAttributeMagnitude(VigorDef, Spec, evaluateParameters, vigor);
    GetCapturedAttributeMagnitude(IntelligenceDef, Spec, evaluateParameters, intelligence);


    vigor = FMath::Max<float>(vigor, 0.f);
    intelligence = FMath::Max<float>(intelligence, 0.f);
    
    ICombatInterface* combatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
    const int32 playerLevel = combatInterface->GetCurrentLevel();
    
    float calcVigor = 1.2f * vigor;
    float calcIntelligence = 0.2f * intelligence;
    
    // 5 + vigor(3) * 1.2 + strength(6) * 2.5 + level(1)
    
    return (playerLevel + calcVigor) * calcIntelligence;
}
