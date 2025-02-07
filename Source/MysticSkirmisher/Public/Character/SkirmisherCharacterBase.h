// Copyright David-6

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "SkirmisherCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)
class MYSTICSKIRMISHER_API ASkirmisherCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ASkirmisherCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet;}
protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() {}

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
	UPROPERTY();
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY();
	TObjectPtr<UAttributeSet> AttributeSet;
};
