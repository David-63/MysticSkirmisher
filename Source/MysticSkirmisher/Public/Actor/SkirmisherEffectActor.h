// Copyright David-6

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffect.h"
#include "SkirmisherEffectActor.generated.h"

class USphereComponent;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnBeginOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	RemoveOnEndOverlap,
	DoNotRemove
};

USTRUCT(BlueprintType)
struct FDurationPolicyType_GE
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EEffectApplicationPolicy EffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EEffectRemovalPolicy EffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> GameplayEffectClass = nullptr;
};

UCLASS()
class MYSTICSKIRMISHER_API ASkirmisherEffectActor : public AActor
{
	GENERATED_BODY()

public:
	ASkirmisherEffectActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, FDurationPolicyType_GE GameplayEffect);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	bool bDestroyOnEffectRemoval = false;

	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(AActor* TargetActor);
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TArray<FDurationPolicyType_GE> DurationPolicy_GE;
};
