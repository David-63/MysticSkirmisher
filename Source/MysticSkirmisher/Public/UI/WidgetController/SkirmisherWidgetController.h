// Copyright David-6

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkirmisherWidgetController.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
/**
 * 
 */
UCLASS()
class MYSTICSKIRMISHER_API USkirmisherWidgetController : public UObject
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;

};
