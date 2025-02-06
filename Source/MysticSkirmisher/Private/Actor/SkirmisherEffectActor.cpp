// Copyright David-6


#include "Actor/SkirmisherEffectActor.h"
#include "AbilitySystem/SkirmisherAttributeSet.h"
#include "AbilitySystem/SkirmisherAbilitySystemComponent.h"

#include "AbilitySystemBlueprintLibrary.h"


ASkirmisherEffectActor::ASkirmisherEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}


void ASkirmisherEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void ASkirmisherEffectActor::ApplyEffectToTarget(AActor *TargetActor, FGameplayEffectPolicySet GameplayEffect)
{
	UAbilitySystemComponent* targetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (targetASC == nullptr) return;

	check(GameplayEffect.GameplayEffectClass);

	
	FGameplayEffectContextHandle effectcontextHandle = targetASC->MakeEffectContext();
	effectcontextHandle.AddSourceObject(this);

	const FGameplayEffectSpecHandle effectSpec = targetASC->MakeOutgoingSpec(GameplayEffect.GameplayEffectClass, GameplayEffect.ActorLevel, effectcontextHandle);
	
	const FActiveGameplayEffectHandle activeEffectHandle = targetASC->ApplyGameplayEffectSpecToSelf(*effectSpec.Data.Get());
	
	const bool bIsInfinite = effectSpec.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;

	if (bIsInfinite && GameplayEffect.EffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(activeEffectHandle, targetASC);
	}
}

void ASkirmisherEffectActor::OnBeginOverlap(AActor *TargetActor)
{
	if (!GameplayEffectPolicySet.IsEmpty())
	{
		for (FGameplayEffectPolicySet& gameplayEffectClass : GameplayEffectPolicySet)
		{
			if (gameplayEffectClass.EffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap)
			{
				ApplyEffectToTarget(TargetActor, gameplayEffectClass);
			}			
		}
	}
}

void ASkirmisherEffectActor::OnEndOverlap(AActor *TargetActor)
{
	if (!GameplayEffectPolicySet.IsEmpty())
	{
		for (FGameplayEffectPolicySet& gameplayEffectClass : GameplayEffectPolicySet)
		{
			if (gameplayEffectClass.EffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
			{
				ApplyEffectToTarget(TargetActor, gameplayEffectClass);
			}

			if (gameplayEffectClass.EffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
			{
				UAbilitySystemComponent* targetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
				if (!IsValid(targetASC)) return;

				TArray<FActiveGameplayEffectHandle> handlesToRemove;
				for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent *> handlePair : ActiveEffectHandles)
				{						
					if (targetASC == handlePair.Value)
					{
						targetASC->RemoveActiveGameplayEffect(handlePair.Key, 1);
						handlesToRemove.Add(handlePair.Key);
					}
				}
				for (FActiveGameplayEffectHandle& handle : handlesToRemove)
				{
					ActiveEffectHandles.FindAndRemoveChecked(handle);
				}
			}
		}
	}
}
