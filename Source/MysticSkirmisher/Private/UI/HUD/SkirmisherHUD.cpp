// Copyright David-6


#include "UI/HUD/SkirmisherHUD.h"
#include "UI/Widget/SkirmisherUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"


UOverlayWidgetController *ASkirmisherHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
    if (OverlayWidgetController == nullptr)
    {
        OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
        OverlayWidgetController->SetWidgetControllerParams(WCParams);
        OverlayWidgetController->BindCallbacksToDependencies();
    }
    return OverlayWidgetController;
}
UAttributeMenuWidgetController *ASkirmisherHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
    if (AttributeMenuWidgetController == nullptr)
    {
        AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
        AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);
        AttributeMenuWidgetController->BindCallbacksToDependencies();
    }
    return AttributeMenuWidgetController;
}

void ASkirmisherHUD::InitOverlay(APlayerController * PC, APlayerState * PS, UAbilitySystemComponent * ASC, UAttributeSet * AS)
{
    checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_SkirmisherHUD"));
    checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_SkirmisherHUD"));

    UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
    OverlayWidget = Cast<USkirmisherUserWidget>(widget);
    
    const FWidgetControllerParams widgetControllerParams(PC, PS, ASC, AS);
    UOverlayWidgetController* overlayWidgetController = GetOverlayWidgetController(widgetControllerParams);
    
    OverlayWidget->SetWidgetController(overlayWidgetController);
    overlayWidgetController->BroadcastInitialValues();

    widget->AddToViewport();

}

