// Copyright David-6


#include "UI/WidgetController/SkirmisherWidgetController.h"


void USkirmisherWidgetController::SetWidgetControllerParams(const FWidgetControllerParams & WCParams)
{
    PlayerController = WCParams.PlayerController;
    PlayerState = WCParams.PlayerState;
    AbilitySystemComponent = WCParams.AbilitySystemComponent;
    AttributeSet = WCParams.AttributeSet;
}
void USkirmisherWidgetController::BroadcastInitialValues()
{
    
}