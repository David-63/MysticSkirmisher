// Copyright David-6

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SkirmisherCharacterBase.generated.h"

UCLASS(Abstract)
class MYSTICSKIRMISHER_API ASkirmisherCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ASkirmisherCharacterBase();

protected:
	virtual void BeginPlay() override;

};
