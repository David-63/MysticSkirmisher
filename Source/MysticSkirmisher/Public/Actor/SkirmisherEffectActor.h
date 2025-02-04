// Copyright David-6

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkirmisherEffectActor.generated.h"

class USphereComponent;

UCLASS()
class MYSTICSKIRMISHER_API ASkirmisherEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASkirmisherEffectActor();

	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);
};
