// Copyright David-6


#include "SkirmisherAssetManager.h"
#include "SkirmisherGameplayTags.h"


USkirmisherAssetManager& USkirmisherAssetManager::Get()
{
    check(GEngine);

    USkirmisherAssetManager* skirmisherManager = Cast<USkirmisherAssetManager>(GEngine->AssetManager);
    return *skirmisherManager;
}

void USkirmisherAssetManager::StartInitialLoading()
{
    Super::StartInitialLoading();
    
    FSkirmisherGameplayTags::InitializeNativeGameplayTags();
}