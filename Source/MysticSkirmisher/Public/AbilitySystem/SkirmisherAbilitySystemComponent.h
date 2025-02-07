// Copyright David-6

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SkirmisherAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class MYSTICSKIRMISHER_API USkirmisherAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	// 자신에게 적용되는 이팩트를 델리게이트로 등록
	void AbilityActorInfoSet();
	
protected:
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);

};
