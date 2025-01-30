// Copyright David-6


#include "Character/SkirmisherEnemy.h"
#include "MysticSkirmisher/MysticSkirmisher.h"
#include "AbilitySystem/SkirmisherAbilitySystemComponent.h"
#include "AbilitySystem/SkirmisherAttributeSet.h"

ASkirmisherEnemy::ASkirmisherEnemy()
{
    GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

    AbilitySystemComponent = CreateDefaultSubobject<USkirmisherAbilitySystemComponent>("AbilitySystemComponent");
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

    AttributeSet = CreateDefaultSubobject<USkirmisherAttributeSet>("AttributeSet");
}

void ASkirmisherEnemy::BeginPlay()
{
    Super::BeginPlay();
    AbilitySystemComponent->InitAbilityActorInfo(this, this);
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
