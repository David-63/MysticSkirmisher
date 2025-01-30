// Copyright David-6


#include "Character/SkirmisherCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

ASkirmisherCharacter::ASkirmisherCharacter()
{
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
    GetCharacterMovement()->bConstrainToPlane = true;
    GetCharacterMovement()->bSnapToPlaneAtStart = true;

    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;
    bUseControllerRotationYaw = false;
}