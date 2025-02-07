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

    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(skirmisherAttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::HealthChanged);
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(skirmisherAttributeSet->GetHealthMaxAttribute()).AddUObject(this, &ThisClass::HealthMaxChanged);
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(skirmisherAttributeSet->GetManaAttribute()).AddUObject(this, &ThisClass::ManaChanged);
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(skirmisherAttributeSet->GetManaMaxAttribute()).AddUObject(this, &ThisClass::ManaMaxChanged);

    Cast<USkirmisherAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda
    (
        [](const FGameplayTagContainer& AssetTags)
        {
            for (const FGameplayTag& tag : AssetTags)
            {
                const FString msg = FString::Printf(TEXT("GE Tag: %s"), *tag.ToString());
                GEngine->AddOnScreenDebugMessage(-1, 0.3f, FColor::Green, msg);
            }
        }
    );
}
void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData &Data) const
{
    OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::HealthMaxChanged(const FOnAttributeChangeData & Data) const
{
    OnHealthMaxChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData &Data) const
{
    OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaMaxChanged(const FOnAttributeChangeData &Data) const
{
    OnManaMaxChanged.Broadcast(Data.NewValue);
}
