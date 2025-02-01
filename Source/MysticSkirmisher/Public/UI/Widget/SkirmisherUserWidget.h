// Copyright David-6

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkirmisherUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYSTICSKIRMISHER_API USkirmisherUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
