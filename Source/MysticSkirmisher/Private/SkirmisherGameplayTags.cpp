// Copyright David-6


#include "SkirmisherGameplayTags.h"
#include "GameplayTagsManager.h"

FSkirmisherGameplayTags FSkirmisherGameplayTags::GameplayTags;


void FSkirmisherGameplayTags::InitializeNativeGameplayTags()
{
    GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("Reduses damage taken, improves block chance"));
}