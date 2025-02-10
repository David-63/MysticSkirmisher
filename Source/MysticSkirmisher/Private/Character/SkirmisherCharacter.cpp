// Copyright David-6


#include "Character/SkirmisherCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/SkirmisherState.h"
#include "Player/SkirmisherController.h"
#include "AbilitySystem/SkirmisherAbilitySystemComponent.h"
#include "AbilitySystem/SkirmisherAttributeSet.h"
#include "UI/HUD/SkirmisherHUD.h"


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
void ASkirmisherCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
    // Init ability actor info for Server
    InitAbilityActorInfo();
}

void ASkirmisherCharacter::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();
    // Init ability actor info for Client
    InitAbilityActorInfo();
}

void ASkirmisherCharacter::InitAbilityActorInfo()
{
    ASkirmisherState* skirmisherState = GetPlayerState<ASkirmisherState>();
    check(skirmisherState);
    skirmisherState->GetAbilitySystemComponent()->InitAbilityActorInfo(skirmisherState, this);
    Cast<USkirmisherAbilitySystemComponent>(skirmisherState->GetAbilitySystemComponent())->AbilityActorInfoSet();

    AbilitySystemComponent = skirmisherState->GetAbilitySystemComponent();
    AttributeSet = skirmisherState->GetAttributeSet();
 
    if (ASkirmisherController* playerController = Cast<ASkirmisherController>(GetController()))
    {
        if (ASkirmisherHUD* skirmisherHUD = Cast<ASkirmisherHUD>(playerController->GetHUD()))
        {
            skirmisherHUD->InitOverlay(playerController, skirmisherState, AbilitySystemComponent, AttributeSet);
        }
    }

    InitializePrimaryAttributes();
}