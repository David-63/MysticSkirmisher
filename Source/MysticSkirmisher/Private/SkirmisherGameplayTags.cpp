// Copyright David-6


#include "SkirmisherGameplayTags.h"
#include "GameplayTagsManager.h"

FSkirmisherGameplayTags FSkirmisherGameplayTags::GameplayTags;


void FSkirmisherGameplayTags::InitializeNativeGameplayTags()
{
    /*
        Primary Attributes
    */
    GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength")
    , FString("Increases physical damage"));
    GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intelligence")
    , FString("Increases magical damage"));
    GameplayTags.Attributes_Primary_Dexterity = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Dexterity")
    , FString("Increases Critical and sub damage"));
    GameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Resilience")
    , FString("Increases armor and penetration"));
    GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vigor")
    , FString("Increases Vital"));
    
    /*
        Secondary Attributes
    */
    GameplayTags.Attributes_Secondary_HealthMax = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthMax")
    , FString("Max of health"));
    GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration")
    , FString("Health regeneration"));
    GameplayTags.Attributes_Secondary_ManaMax = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaMax")
    , FString("Max of mana"));
    GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration")
    , FString("Mana regeneration"));
    GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor")
    , FString("Reduses damage taken, improves block chance"));
    GameplayTags.Attributes_Secondary_Block = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Block")
    , FString("Chance to cut incoming damage in half"));
    GameplayTags.Attributes_Secondary_Penetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Penetration")
    , FString("Ignores percentage of enemy armor, increase critical hit chance"));
    GameplayTags.Attributes_Secondary_CriticalChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalChance")
    , FString("Chance to more damage plus critical hit bonus"));
    GameplayTags.Attributes_Secondary_CriticalDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalDamage")
    , FString("Bonus damage added when a critical hit is scored"));
    GameplayTags.Attributes_Secondary_CriticalResilience = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalResilience")
    , FString("Reduses critical hit chance of attacking enemies"));
    
    /*
        Vital Attributes
    */
    GameplayTags.Attributes_Vital_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Health"), FString("Amount of damage a player can take before death"));
    GameplayTags.Attributes_Vital_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Mana"), FString("A resource used to cast spells"));

    /*
        Input Tags
    */
   GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB")
   , FString("Input tag for Left Mouse Button"));
   GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB")
   , FString("Input tag for Right Mouse Button"));
   
   GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.1")
   , FString("Input tag for 1 key"));
   GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.2")
   , FString("Input tag for 2 key"));
   GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.3")
   , FString("Input tag for 3 key"));
   GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.4")
   , FString("Input tag for 4 key"));

}