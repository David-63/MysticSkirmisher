// Copyright David-6

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SkirmisherHUD.generated.h"


struct FWidgetControllerParams;
class USkirmisherUserWidget;
class UAbilitySystemComponent;
class UAttributeSet;
class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class MYSTICSKIRMISHER_API ASkirmisherHUD : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TObjectPtr<USkirmisherUserWidget> OverlayWidget;

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<USkirmisherUserWidget> OverlayWidgetClass;
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

};
