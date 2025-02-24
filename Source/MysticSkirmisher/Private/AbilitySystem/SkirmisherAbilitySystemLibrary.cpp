// Copyright David-6


#include "AbilitySystem/SkirmisherAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/SkirmisherHUD.h"
#include "UI/WidgetController/SkirmisherWidgetController.h"
#include "Player/SkirmisherState.h"
#include "Game/SkirmisherGameModeBase.h"
#include "AbilitySystem/SkirmisherAbilitySystemComponent.h"

UOverlayWidgetController* USkirmisherAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{    
    if (APlayerController* playerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
    {
        if (ASkirmisherHUD* skirmisherHUD = Cast<ASkirmisherHUD>(playerController->GetHUD()))
        {
            ASkirmisherState* playerState = playerController->GetPlayerState<ASkirmisherState>();
            UAbilitySystemComponent* abilitySystemComponent = playerState->GetAbilitySystemComponent();
            UAttributeSet* attributeSet = playerState->GetAttributeSet();
            const FWidgetControllerParams widgetControllerParams(playerController, playerState, abilitySystemComponent, attributeSet);


            return skirmisherHUD->GetOverlayWidgetController(widgetControllerParams);
        }
    }

    return nullptr;
}

UAttributeMenuWidgetController* USkirmisherAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
    if (APlayerController* pc = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
    {
        if (ASkirmisherHUD* skirmisherHUD = Cast<ASkirmisherHUD>(pc->GetHUD()))
        {
            ASkirmisherState* ps = pc->GetPlayerState<ASkirmisherState>();
            UAbilitySystemComponent* asc = ps->GetAbilitySystemComponent();
            UAttributeSet* as = ps->GetAttributeSet();
            const FWidgetControllerParams wcp(pc, ps, asc, as);

            return skirmisherHUD->GetAttributeMenuWidgetController(wcp);
        }
    }

    return nullptr;
}

void USkirmisherAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
    ASkirmisherGameModeBase* gameMode = Cast<ASkirmisherGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
    if (gameMode == nullptr) return;

    AActor* avatarActor = ASC->GetAvatarActor();

    UCharacterClassInfo* characterClassInfo = gameMode->CharacterClassInfo;
    FCharacterClassDefaultInfo classDefaultInfo = characterClassInfo->GetClassDefaultInfo(CharacterClass);


    FGameplayEffectContextHandle primaryAttributesContextHandle = ASC->MakeEffectContext();
    primaryAttributesContextHandle.AddSourceObject(avatarActor);
    const FGameplayEffectSpecHandle primaryAttributesSpecHandle = ASC->MakeOutgoingSpec(classDefaultInfo.PrimaryAttributes, Level, primaryAttributesContextHandle);
    ASC->ApplyGameplayEffectSpecToSelf(*primaryAttributesSpecHandle.Data.Get());


    FGameplayEffectContextHandle secondaryAttributeContextHandle = ASC->MakeEffectContext();
    secondaryAttributeContextHandle.AddSourceObject(avatarActor);
    const FGameplayEffectSpecHandle secondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(characterClassInfo->SecondaryAttributes, Level, secondaryAttributeContextHandle);
    ASC->ApplyGameplayEffectSpecToSelf(*secondaryAttributesSpecHandle.Data.Get());


    FGameplayEffectContextHandle vitalAttributeContextHandle = ASC->MakeEffectContext();
    vitalAttributeContextHandle.AddSourceObject(avatarActor);
    const FGameplayEffectSpecHandle vitalAttributesSpecHandle = ASC->MakeOutgoingSpec(characterClassInfo->VitalAttributes, Level, vitalAttributeContextHandle);
    ASC->ApplyGameplayEffectSpecToSelf(*vitalAttributesSpecHandle.Data.Get());
}