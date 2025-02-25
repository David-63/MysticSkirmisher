// Copyright David-6

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "SkirmisherAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


USTRUCT(BlueprintType)
struct FEffectProperties
{
	GENERATED_BODY()
	FEffectProperties() {}

public:
	UPROPERTY()
	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;	
	UPROPERTY()
	AController* SourceController = nullptr;
	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;
	
	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;
	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;	
	UPROPERTY()
	AController* TargetController = nullptr;
	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};


template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

/**
 * 	MysticSkirmisher 에서 사용하는 AttributeSet 클래스
 * 
 * 	Player 가 사용할 Attribute에 메크로함수를 적용하여 외부에서 GetSet을 사용할 수 있음
 */
UCLASS()
class MYSTICSKIRMISHER_API USkirmisherAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	USkirmisherAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// 어트리뷰트가 적용되기 직전에 먼저 호출되는 함수 (사전에 입력되는 Value 값을 제어할 수 있음)
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	// GE가 적용될 때 Source와 Target에 접근하도록 해주는 함수
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;

	/*
		Vital Attributes
	*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(USkirmisherAttributeSet, Health);
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& PrevHealth) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(USkirmisherAttributeSet, Mana);
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& PrevMana) const;



	/*
		Meta Attributes
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(USkirmisherAttributeSet, IncomingDamage);


	
	/*
		Primary Attributes
	*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(USkirmisherAttributeSet, Strength);
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& PrevStrength) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "Primary Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(USkirmisherAttributeSet, Intelligence);
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& PrevIntelligence) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category = "Primary Attributes")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(USkirmisherAttributeSet, Resilience);
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& PrevResilience) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category = "Primary Attributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(USkirmisherAttributeSet, Vigor);
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& PrevVigor) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Dexterity, Category = "Primary Attributes")
	FGameplayAttributeData Dexterity;
	ATTRIBUTE_ACCESSORS(USkirmisherAttributeSet, Dexterity);
	UFUNCTION()
	void OnRep_Dexterity(const FGameplayAttributeData& PrevDexterity) const;

	/*
		Secondary Attributes
	*/

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Secondary Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(USkirmisherAttributeSet, Armor);
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& PrevArmor) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Block, Category = "Secondary Attributes")
	FGameplayAttributeData Block;
	ATTRIBUTE_ACCESSORS(USkirmisherAttributeSet, Block);
	UFUNCTION()
	void OnRep_Block(const FGameplayAttributeData& PrevBlock) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Penetration, Category = "Secondary Attributes")
	FGameplayAttributeData Penetration;
	ATTRIBUTE_ACCESSORS(USkirmisherAttributeSet, Penetration);
	UFUNCTION()
	void OnRep_Penetration(const FGameplayAttributeData& PrevPenetration) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalChance, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalChance;
	ATTRIBUTE_ACCESSORS(USkirmisherAttributeSet, CriticalChance);
	UFUNCTION()
	void OnRep_CriticalChance(const FGameplayAttributeData& PrevCriticalChance) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalDamage, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalDamage;
	ATTRIBUTE_ACCESSORS(USkirmisherAttributeSet, CriticalDamage);
	UFUNCTION()
	void OnRep_CriticalDamage(const FGameplayAttributeData& PrevCriticalDamage) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalResilience, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalResilience;
	ATTRIBUTE_ACCESSORS(USkirmisherAttributeSet, CriticalResilience);
	UFUNCTION()
	void OnRep_CriticalResilience(const FGameplayAttributeData& PrevCriticalResilience) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(USkirmisherAttributeSet, HealthRegeneration);
	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& PrevHealthRegeneration) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(USkirmisherAttributeSet, ManaRegeneration);
	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& PrevManaRegeneration) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthMax, Category = "Secondary Attributes")
	FGameplayAttributeData HealthMax;
	ATTRIBUTE_ACCESSORS(USkirmisherAttributeSet, HealthMax);
	UFUNCTION()
	void OnRep_HealthMax(const FGameplayAttributeData& PrevHealthMax) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaMax, Category = "Secondary Attributes")
	FGameplayAttributeData ManaMax;
	ATTRIBUTE_ACCESSORS(USkirmisherAttributeSet, ManaMax);
	UFUNCTION()
	void OnRep_ManaMax(const FGameplayAttributeData& PrevManaMax) const;

private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
