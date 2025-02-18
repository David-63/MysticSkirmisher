// Copyright David-6

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SkirmisherController.generated.h"


class UInputMappingContext;
class UInputAction;
class IEnemyInterface;
class USkirmisherInputConfig;
struct FGameplayTag;
class USkirmisherAbilitySystemComponent;
class USplineComponent;
/**
 * 
 */
UCLASS()
class MYSTICSKIRMISHER_API ASkirmisherController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASkirmisherController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
public:
	virtual void PlayerTick(float DeltaTime) override;

private:
	/*
		Input Func
	*/
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> InputContext;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Move;

	void ActionMove(const struct FInputActionValue& InputValue);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<USkirmisherInputConfig> InputConfig;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY()
	TObjectPtr<USkirmisherAbilitySystemComponent> SkirmisherAbilitySystemComponent;
	USkirmisherAbilitySystemComponent* GetASC();

	/*
		Highlight enemy
	*/
	void CursorTrace();
	TScriptInterface<IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> ThisActor;
	FHitResult CursorHit;


	/*
		Click to move
	*/
	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.f;
	float ShortPressThreshold = 0.2f;
	bool bAutoRunning = false;
	bool bTargeting = false;

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

	void AutoRun();
};
