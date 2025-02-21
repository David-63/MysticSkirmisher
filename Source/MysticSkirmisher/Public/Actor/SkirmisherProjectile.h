// Copyright David-6

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "SkirmisherProjectile.generated.h"


class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;

UCLASS()
class MYSTICSKIRMISHER_API ASkirmisherProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASkirmisherProjectile();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;

	
protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(EditAnywhere, Category = "Assets")
	TObjectPtr<UNiagaraSystem> ImpactEffect;

	UPROPERTY(EditAnywhere, Category = "Assets")
	TObjectPtr<USoundBase> ImpactSound;

	bool bBeginOverlap = false;

	UPROPERTY(EditAnywhere, Category = "Assets")
	TObjectPtr<USoundBase> LoopingSound;

	UPROPERTY();
	TObjectPtr<UAudioComponent> LoopingSoundComponent;


	UPROPERTY(EditDefaultsOnly)
	float LifeSpan = 2.f;
};
