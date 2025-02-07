// Copyright David-6


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/SkirmisherAttributeSet.h"
#include "AbilitySystem/SkirmisherAbilitySystemComponent.h"



void UOverlayWidgetController::BroadcastInitialValues()
{
    const USkirmisherAttributeSet* skirmisherAttributeSet = CastChecked<USkirmisherAttributeSet>(AttributeSet);
    OnHealthChanged.Broadcast(skirmisherAttributeSet->GetHealth());
    OnHealthMaxChanged.Broadcast(skirmisherAttributeSet->GetHealthMax());
    OnManaChanged.Broadcast(skirmisherAttributeSet->GetMana());
    OnManaMaxChanged.Broadcast(skirmisherAttributeSet->GetManaMax());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
    const USkirmisherAttributeSet* skirmisherAttributeSet = CastChecked<USkirmisherAttributeSet>(AttributeSet);

    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(skirmisherAttributeSet->GetHealthAttribute()).AddLambda
    (
        [this](const FOnAttributeChangeData& Data)
        {
            OnHealthChanged.Broadcast(Data.NewValue);
        }
    );
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(skirmisherAttributeSet->GetHealthMaxAttribute()).AddLambda
    (
        [this](const FOnAttributeChangeData& Data)
        {
            OnHealthMaxChanged.Broadcast(Data.NewValue);
        }
    );
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(skirmisherAttributeSet->GetManaAttribute()).AddLambda
    (
        [this](const FOnAttributeChangeData& Data)
        {
            OnManaChanged.Broadcast(Data.NewValue);
        }
    );
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(skirmisherAttributeSet->GetManaMaxAttribute()).AddLambda
    (
        [this](const FOnAttributeChangeData& Data)
        {
            OnManaMaxChanged.Broadcast(Data.NewValue);
        }
    );

    Cast<USkirmisherAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda
    (
        // 람다 사용법: [범위](인자){로직}
        [this](const FGameplayTagContainer& AssetTags)
        {
            for (const FGameplayTag& tag : AssetTags)
            {
                // {"A.1"}.HasAny({"A","B"}) will return True, {"A"}.HasAny({"A.1","B"}) will return False
                FGameplayTag messageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
                if (tag.MatchesTag(messageTag))
                {
                    FWidgetRow* row = GetDataTableRowByTag<FWidgetRow>(MessageWidgetDataTable, tag);
                    MessageWidgetRowDeletage.Broadcast(*row);
                }
            }
        }
    );
}