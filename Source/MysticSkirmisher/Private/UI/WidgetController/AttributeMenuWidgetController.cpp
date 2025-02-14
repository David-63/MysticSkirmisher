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

    FSkirmisherAttributeInfo info = AttributeInfo->FindAttributeInfoForTag(FSkirmisherGameplayTags::Get().Attributes_Primary_Strength);
    info.AttributeValue = skirmisherAttributeSet->GetStrength();    
    AttributeInfoDelegate.Broadcast(info);

}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
}