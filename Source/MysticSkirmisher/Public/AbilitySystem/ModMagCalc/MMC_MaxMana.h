// Copyright David-6

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxMana.generated.h"

/**
 * 	최대 마나 계산식
 * 	다른 GameplayTag 에 존재하는 Attribute에 의해 최대 마나를 계산하는 기능
 */
UCLASS()
class MYSTICSKIRMISHER_API UMMC_MaxMana : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UMMC_MaxMana();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	FGameplayEffectAttributeCaptureDefinition VigorDef;
	FGameplayEffectAttributeCaptureDefinition IntelligenceDef;
};

