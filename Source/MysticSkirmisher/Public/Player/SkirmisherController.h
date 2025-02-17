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
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> InputContext;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Move;

	void ActionMove(const struct FInputActionValue& InputValue);

	void CursorTrace();
	TScriptInterface<IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> ThisActor;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<USkirmisherInputConfig> InputConfig;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY()
	TObjectPtr<USkirmisherAbilitySystemComponent> SkirmisherAbilitySystemComponent;

	USkirmisherAbilitySystemComponent* GetASC();
};
