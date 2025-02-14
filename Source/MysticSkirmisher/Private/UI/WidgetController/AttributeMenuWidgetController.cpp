// Copyright David-6


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/SkirmisherAttributeSet.h"
//#include "AbilitySystem/SkirmisherAbilitySystemComponent.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "SkirmisherGameplayTags.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
    check(AttributeInfo);
    const USkirmisherAttributeSet* skirmisherAttributeSet = CastChecked<USkirmisherAttributeSet>(AttributeSet);

    for (auto& pair : skirmisherAttributeSet->TagsToAttributes)
    {
        FSkirmisherAttributeInfo info = AttributeInfo->FindAttributeInfoForTag(pair.Key);        
        info.AttributeValue = pair.Value().GetNumericValue(skirmisherAttributeSet);
        AttributeInfoDelegate.Broadcast(info);
    }
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
}