// Copyright David-6

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "SkirmisherState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
/**
 * 
 */
UCLASS()
class MYSTICSKIRMISHER_API ASkirmisherState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	ASkirmisherState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet;}
	FORCEINLINE int32 GetCurrentLevel() const { return Level; }

protected:
	UPROPERTY(VisibleAnywhere);
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY();
	TObjectPtr<UAttributeSet> AttributeSet;

private:
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Level)
	int32 Level = 1;

	UFUNCTION()
	void OnRep_Level(int32 PrevLevel);
};
