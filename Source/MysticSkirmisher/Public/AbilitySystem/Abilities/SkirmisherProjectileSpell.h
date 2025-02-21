// Copyright David-6

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SkirmisherGameplayAbility.h"
#include "SkirmisherProjectileSpell.generated.h"

class ASkirmisherProjectile;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class MYSTICSKIRMISHER_API USkirmisherProjectileSpell : public USkirmisherGameplayAbility
{
	GENERATED_BODY()
	
protected:
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SpawnProjectile(const FVector& ProjectileTargetLocation);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ASkirmisherProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;
};
