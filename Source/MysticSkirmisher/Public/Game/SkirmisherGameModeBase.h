// Copyright David-6

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SkirmisherGameModeBase.generated.h"

class UCharacterClassInfo;
/**
 * 
 */
UCLASS()
class MYSTICSKIRMISHER_API ASkirmisherGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;
};
