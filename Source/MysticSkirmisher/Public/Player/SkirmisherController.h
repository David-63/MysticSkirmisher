// Copyright David-6

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SkirmisherController.generated.h"


class UInputMappingContext;
class UInputAction;
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

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> InputContext;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Move;

	void ActionMove(const struct FInputActionValue& InputValue);
	
};
