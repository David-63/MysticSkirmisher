// Copyright David-6


#include "Character/SkirmisherCharacterBase.h"

ASkirmisherCharacterBase::ASkirmisherCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASkirmisherCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

