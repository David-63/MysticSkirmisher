// Copyright David-6

#pragma once

#include "CoreMinimal.h"
#include "Character/SkirmisherCharacterBase.h"
#include "SkirmisherCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MYSTICSKIRMISHER_API ASkirmisherCharacter : public ASkirmisherCharacterBase
{
	GENERATED_BODY()
public:
	ASkirmisherCharacter();

    virtual void PossessedBy(AController *NewController) override;
    virtual void OnRep_PlayerState() override;

private:
	void InitAbilityActorInfo();

};
