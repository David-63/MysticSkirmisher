// Copyright David-6


#include "SkirmisherCharacterBase.h"

// Sets default values
ASkirmisherCharacterBase::ASkirmisherCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASkirmisherCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkirmisherCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASkirmisherCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

