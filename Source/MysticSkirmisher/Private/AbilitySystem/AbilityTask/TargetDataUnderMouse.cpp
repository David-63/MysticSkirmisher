// Copyright David-6


#include "AbilitySystem/AbilityTask/TargetDataUnderMouse.h"
#include "Player/SkirmisherController.h"
#include "AbilitySystemComponent.h"


UTargetDataUnderMouse *UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility *OwningAbility)
{
    UTargetDataUnderMouse* myObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
    return myObj;
}

void UTargetDataUnderMouse::Activate()
{
    const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();

    if (bIsLocallyControlled)
    {
        SendMouseCursorData();
    }
    else
    {
        // TODO: We are on the server, so listen for target data.

    }

}
void UTargetDataUnderMouse::SendMouseCursorData()
{
    FScopedPredictionWindow scopedPrediction(AbilitySystemComponent.Get());

    FGameplayAbilityTargetData_SingleTargetHit* data = new FGameplayAbilityTargetData_SingleTargetHit();

    FGameplayAbilityTargetDataHandle dataHandle;

    ASkirmisherController* pc = Cast<ASkirmisherController>(Ability->GetCurrentActorInfo()->PlayerController);
    data->HitResult = pc->GetCursorHit();
    dataHandle.Add(data);
    

    AbilitySystemComponent->ServerSetReplicatedTargetData
    (
        GetAbilitySpecHandle(), GetActivationPredictionKey(), dataHandle, FGameplayTag(), AbilitySystemComponent->ScopedPredictionKey
    );

    if (ShouldBroadcastAbilityTaskDelegates())
    {
        ValidData.Broadcast(dataHandle);
    }
}