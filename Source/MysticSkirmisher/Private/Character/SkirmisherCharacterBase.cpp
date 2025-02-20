// Copyright David-6


#include "Character/SkirmisherCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/SkirmisherAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "MysticSkirmisher/MysticSkirmisher.h"


ASkirmisherCharacterBase::ASkirmisherCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent * ASkirmisherCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ASkirmisherCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector ASkirmisherCharacterBase::GetCombatSocketLocation()
{
	check(Weapon);
	return Weapon->GetSocketLocation(WeaponTipSocketName);
}


void ASkirmisherCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
    check(IsValid(GetAbilitySystemComponent()));
    check(GameplayEffectClass);

    FGameplayEffectContextHandle contextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	contextHandle.AddSourceObject(this);
    const FGameplayEffectSpecHandle specHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, contextHandle);
    GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*specHandle.Data.Get(), GetAbilitySystemComponent());
}

void ASkirmisherCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);	
}

void ASkirmisherCharacterBase::AddCharacterAbilities()
{
	USkirmisherAbilitySystemComponent* skirmisherASC = CastChecked<USkirmisherAbilitySystemComponent>(GetAbilitySystemComponent());
	if (!HasAuthority()) return;

	skirmisherASC->AddCharacterAbilities(StartupAbiliities);
}
