// Copyright David-6


#include "Character/SkirmisherEnemy.h"
#include "MysticSkirmisher/MysticSkirmisher.h"
#include "AbilitySystem/SkirmisherAttributeSet.h"
#include "AbilitySystem/SkirmisherAbilitySystemComponent.h"
#include "AbilitySystem/SkirmisherAbilitySystemLibrary.h"
#include "Components/WidgetComponent.h"
#include "UI/Widget/SkirmisherUserWidget.h"
#include "MysticSkirmisher/MysticSkirmisher.h"
#include "Components/SphereComponent.h"

ASkirmisherEnemy::ASkirmisherEnemy()
{
    GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);


    SenseAreaComponent = CreateDefaultSubobject<USphereComponent>("SenseArea");
	SenseAreaComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SenseAreaComponent->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
    SenseAreaComponent->SetupAttachment(GetRootComponent());

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

void ASkirmisherEnemy::InitializeDefaultAttributes() const
{
    USkirmisherAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, GetAbilitySystemComponent());

}
