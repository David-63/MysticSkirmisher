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
        const FGameplayAbilitySpecHandle specHandle = GetAbilitySpecHandle();
        const FPredictionKey activationPredictionKey = GetActivationPredictionKey();
        AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(specHandle, activationPredictionKey).AddUObject(this, &UTargetDataUnderMouse::OnTargetDataReplicatedCallback);
        const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(specHandle, activationPredictionKey);
        if (!bCalledDelegate)
        {
            SetWaitingOnRemotePlayerData();
        }
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

void UTargetDataUnderMouse::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle & DataHandle, FGameplayTag ActivationTag)
{
    AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());

    if (ShouldBroadcastAbilityTaskDelegates())
    {
        ValidData.Broadcast(DataHandle);
    }

}