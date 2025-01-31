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

	UFUNCTION()
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;
};
