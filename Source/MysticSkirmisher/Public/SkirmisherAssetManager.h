// Copyright David-6

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "SkirmisherAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class MYSTICSKIRMISHER_API USkirmisherAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	static USkirmisherAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
