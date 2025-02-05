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

void ASkirmisherEffectActor::ApplyEffectToTarget(AActor *TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* targetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (targetASC == nullptr) return;
	check(GameplayEffectClass);

	FGameplayEffectContextHandle effectcontextHandle = targetASC->MakeEffectContext();
	effectcontextHandle.AddSourceObject(this);

	const FGameplayEffectSpecHandle effectSpec = targetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, effectcontextHandle);
	
	const FActiveGameplayEffectHandle activeEffectHandle = targetASC->ApplyGameplayEffectSpecToSelf(*effectSpec.Data.Get());
	
	const bool bIsInfinite = effectSpec.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UE_LOG(LogTemp, Warning, TEXT("Add Queue"));
		ActiveEffectHandles.Add(activeEffectHandle, targetASC);
	}
}

void ASkirmisherEffectActor::OnBeginOverlap(AActor *TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
}

void ASkirmisherEffectActor::OnEndOverlap(AActor *TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
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
