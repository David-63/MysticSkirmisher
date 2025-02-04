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

void ASkirmisherEffectActor::ApplyEffectToTarget(AActor *Target, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* targetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	if (targetASC == nullptr) return;
	check(GameplayEffectClass);

	FGameplayEffectContextHandle effectcontextHandle = targetASC->MakeEffectContext();
	effectcontextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle effectSpec = targetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, effectcontextHandle);
	targetASC->ApplyGameplayEffectSpecToSelf(*effectSpec.Data.Get());
}
