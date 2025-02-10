// Copyright David-6


#include "Character/SkirmisherCharacterBase.h"
#include "AbilitySystemComponent.h"

ASkirmisherCharacterBase::ASkirmisherCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent * ASkirmisherCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ASkirmisherCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASkirmisherCharacterBase::InitializePrimaryAttributes() const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(DefaultPrimaryAttributes);
	
	const FGameplayEffectContextHandle contextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle specHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultPrimaryAttributes, 1.f, contextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*specHandle.Data.Get(), GetAbilitySystemComponent());

}
