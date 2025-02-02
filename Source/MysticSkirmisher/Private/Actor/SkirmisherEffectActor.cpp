// Copyright David-6


#include "Actor/SkirmisherEffectActor.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/SkirmisherAttributeSet.h"

ASkirmisherEffectActor::ASkirmisherEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere");
	SphereComponent->SetupAttachment(GetRootComponent());

}

void ASkirmisherEffectActor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TODO: Change this to apply a Gameplay Effect. For now, using const_cast as a hack!
	if (IAbilitySystemInterface* ASInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const USkirmisherAttributeSet* attributeSet = Cast<USkirmisherAttributeSet>(ASInterface->GetAbilitySystemComponent()->GetAttributeSet(USkirmisherAttributeSet::StaticClass()));
		USkirmisherAttributeSet* mutableAttributeSet = const_cast<USkirmisherAttributeSet*>(attributeSet);
		
		mutableAttributeSet->SetHealth(attributeSet->GetHealth() + 10.f);
		mutableAttributeSet->SetMana(attributeSet->GetMana() + 10.f);
		Destroy();
	}
}
void ASkirmisherEffectActor::EndOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
}
void ASkirmisherEffectActor::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ASkirmisherEffectActor::BeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ASkirmisherEffectActor::EndOverlap);
}

