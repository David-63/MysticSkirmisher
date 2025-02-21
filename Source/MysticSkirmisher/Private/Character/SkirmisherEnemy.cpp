// Copyright David-6


#include "Character/SkirmisherEnemy.h"
#include "MysticSkirmisher/MysticSkirmisher.h"
#include "AbilitySystem/SkirmisherAbilitySystemComponent.h"
#include "AbilitySystem/SkirmisherAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "UI/Widget/SkirmisherUserWidget.h"

ASkirmisherEnemy::ASkirmisherEnemy()
{
    GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

    AbilitySystemComponent = CreateDefaultSubobject<USkirmisherAbilitySystemComponent>("AbilitySystemComponent");
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

    AttributeSet = CreateDefaultSubobject<USkirmisherAttributeSet>("AttributeSet");

    HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBarWidget");
    HealthBar->SetupAttachment(GetRootComponent());
}

void ASkirmisherEnemy::BeginPlay()
{
    Super::BeginPlay();
    InitAbilityActorInfo();

    if (USkirmisherUserWidget* skrimisherUserWidget = Cast<USkirmisherUserWidget>(HealthBar->GetUserWidgetObject()))
    {
        skrimisherUserWidget->SetWidgetController(this);
    }

    if (const USkirmisherAttributeSet* skrimisherAS = Cast<USkirmisherAttributeSet>(AttributeSet))
    {
        AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(skrimisherAS->GetHealthAttribute()).AddLambda
        (
            [this](const FOnAttributeChangeData& Data)
            {
                OnHealthChanged.Broadcast(Data.NewValue);
            }
        );
        AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(skrimisherAS->GetHealthMaxAttribute()).AddLambda
        (
            [this](const FOnAttributeChangeData& Data)
            {
                OnHealthMaxChanged.Broadcast(Data.NewValue);
            }
        );

        OnHealthChanged.Broadcast(skrimisherAS->GetHealth());
        OnHealthMaxChanged.Broadcast(skrimisherAS->GetHealthMax());
    }
    
}

void ASkirmisherEnemy::InitAbilityActorInfo()
{
    AbilitySystemComponent->InitAbilityActorInfo(this, this);
    Cast<USkirmisherAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

    InitializeDefaultAttributes();
}
void ASkirmisherEnemy::HighlightActor()
{
    GetMesh()->SetRenderCustomDepth(true);
    GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
    Weapon->SetRenderCustomDepth(true);
    Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void ASkirmisherEnemy::UnHighlightActor()
{
    GetMesh()->SetRenderCustomDepth(false);
    Weapon->SetRenderCustomDepth(false);    
}

int32 ASkirmisherEnemy::GetCurrentLevel()
{
    return Level;
}
