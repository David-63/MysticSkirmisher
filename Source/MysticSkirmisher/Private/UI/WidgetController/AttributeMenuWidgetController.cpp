// Copyright David-6


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/SkirmisherAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
    check(AttributeInfo);
    const USkirmisherAttributeSet* skirmisherAttributeSet = CastChecked<USkirmisherAttributeSet>(AttributeSet);

    for (auto& pair : skirmisherAttributeSet->TagsToAttributes)
    {
        BroadcastAttributeInfo(pair.Key, pair.Value());
    }
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
    check(AttributeInfo);
    const USkirmisherAttributeSet* skirmisherAttributeSet = CastChecked<USkirmisherAttributeSet>(AttributeSet);

    for (auto& pair : skirmisherAttributeSet->TagsToAttributes)
    {
        AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(pair.Value()).AddLambda
        (
            [this, pair](const FOnAttributeChangeData& Data)
            {
                BroadcastAttributeInfo(pair.Key, pair.Value());
            }
        );
    }

}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag &AttributeTag, const FGameplayAttribute &Attribute) const
{
    FSkirmisherAttributeInfo info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
    info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
    AttributeInfoDelegate.Broadcast(info);
}
