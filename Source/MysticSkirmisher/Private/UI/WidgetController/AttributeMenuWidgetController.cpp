// Copyright David-6


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/SkirmisherAttributeSet.h"
#include "AbilitySystem/SkirmisherAbilitySystemComponent.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
    const USkirmisherAttributeSet* skirmisherAttributeSet = CastChecked<USkirmisherAttributeSet>(AttributeSet);
 
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
}