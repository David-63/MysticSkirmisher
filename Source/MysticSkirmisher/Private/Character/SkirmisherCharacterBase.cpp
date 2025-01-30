// Copyright David-6


#include "Character/SkirmisherCharacterBase.h"

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

