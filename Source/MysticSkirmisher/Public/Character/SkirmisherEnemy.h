// Copyright David-6

#pragma once

#include "CoreMinimal.h"
#include "Character/SkirmisherCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "SkirmisherEnemy.generated.h"

/**
 * 
 */
UCLASS()
class MYSTICSKIRMISHER_API ASkirmisherEnemy : public ASkirmisherCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
public:
	ASkirmisherEnemy();
	
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;

public:
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
};
