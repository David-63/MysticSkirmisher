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
	
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Dexterity;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;

	FGameplayTag Attributes_Secondary_HealthMax;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaMax;	
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_Block;
	FGameplayTag Attributes_Secondary_Penetration;
	FGameplayTag Attributes_Secondary_CriticalChance;
	FGameplayTag Attributes_Secondary_CriticalDamage;
	FGameplayTag Attributes_Secondary_CriticalResilience;
	
	FGameplayTag Attributes_Vital_Health;
	FGameplayTag Attributes_Vital_Mana;
	
protected:
	
private:
	static FSkirmisherGameplayTags GameplayTags;
};