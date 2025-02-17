// Copyright David-6


#include "Input/SkirmisherInputConfig.h"

const UInputAction *USkirmisherInputConfig::FindAbilityInputActionForTag(const FGameplayTag &InputTag, bool bLogNotFound) const
{
    for (const FSkirmisherInputAction& inputAction : AbilityInputActions)
    {
        if (inputAction.InputTag == InputTag)
        {
            return inputAction.InputAction;
        }
    }
    if (bLogNotFound)
    {
        UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s], on InputConfig [%s]"), *InputTag.ToString(), *GetNameSafe(this));
    }
    return nullptr;
}