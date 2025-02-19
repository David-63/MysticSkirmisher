// Copyright David-6


#include "AbilitySystem/AbilityTask/TargetDataUnderMouse.h"
#include "Player/SkirmisherController.h"


UTargetDataUnderMouse *UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility *OwningAbility)
{
    UTargetDataUnderMouse* myObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
    return myObj;
}

void UTargetDataUnderMouse::Activate()
{
    ASkirmisherController* pc = Cast<ASkirmisherController>(Ability->GetCurrentActorInfo()->PlayerController);
    //APlayerController* pc = Ability->GetCurrentActorInfo()->PlayerController.Get();
    //FHitResult hit;
    //pc->GetHitResultUnderCursor(ECC_Visibility, false, hit);

    ValidData.Broadcast(pc->GetCursorHit().Location);
}