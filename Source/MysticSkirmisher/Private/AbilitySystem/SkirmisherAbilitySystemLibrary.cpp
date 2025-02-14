// Copyright David-6


#include "AbilitySystem/SkirmisherAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/SkirmisherHUD.h"
#include "UI/WidgetController/SkirmisherWidgetController.h"
#include "Player/SkirmisherState.h"

UOverlayWidgetController* USkirmisherAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{    
    if (APlayerController* playerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
    {
        if (ASkirmisherHUD* skirmisherHUD = Cast<ASkirmisherHUD>(playerController->GetHUD()))
        {
            ASkirmisherState* playerState = playerController->GetPlayerState<ASkirmisherState>();
            UAbilitySystemComponent* abilitySystemComponent = playerState->GetAbilitySystemComponent();
            UAttributeSet* attributeSet = playerState->GetAttributeSet();
            const FWidgetControllerParams widgetControllerParams(playerController, playerState, abilitySystemComponent, attributeSet);


            return skirmisherHUD->GetOverlayWidgetController(widgetControllerParams);
        }
    }

    return nullptr;
}
