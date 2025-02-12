// Copyright David-6

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * 	SkirmisherGameplayTags
 * 
 * 	Singleton containing native Gameplay Tags
 */

struct FSkirmisherGameplayTags
{
public:
	static const FSkirmisherGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();
	
	FGameplayTag Attributes_Secondary_Armor;
protected:
	
private:
	static FSkirmisherGameplayTags GameplayTags;
};