// Copyright David-6


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/SkirmisherAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
    const USkirmisherAttributeSet* skirmisherAttributeSet = CastChecked<USkirmisherAttributeSet>(AttributeSet);    
    OnHealthChanged.Broadcast(skirmisherAttributeSet->GetHealth());
    OnHealthMaxChanged.Broadcast(skirmisherAttributeSet->GetHealthMax());
}