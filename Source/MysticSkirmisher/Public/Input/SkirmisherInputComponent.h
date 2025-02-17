// Copyright David-6

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "SkirmisherInputConfig.h"
#include "SkirmisherInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class MYSTICSKIRMISHER_API USkirmisherInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
public:
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>	
	void BindAbilityActions(const USkirmisherInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);

};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
inline void USkirmisherInputComponent::BindAbilityActions(const USkirmisherInputConfig *InputConfig, UserClass *Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConfig);

	for (const FSkirmisherInputAction& action : InputConfig->AbilityInputActions)
	{
		if (action.InputAction && action.InputTag.IsValid())
		{			
			if (PressedFunc)
			{
				BindAction(action.InputAction, ETriggerEvent::Started, Object, PressedFunc, action.InputTag);
			}
			if (ReleasedFunc)
			{
				BindAction(action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, action.InputTag);
			}
			if (HeldFunc)
			{
				BindAction(action.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, action.InputTag);
			}
		}
	}
}
