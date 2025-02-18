// Copyright David-6


#include "Player/SkirmisherController.h"
#include "EnhancedInputSubsystems.h"
#include "Interaction/EnemyInterface.h"
#include "GameplayTagContainer.h"
#include "Input/SkirmisherInputComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/SkirmisherAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "SkirmisherGameplayTags.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"


ASkirmisherController::ASkirmisherController()
{
    bReplicates = true;

    Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void ASkirmisherController::BeginPlay()
{
    Super::BeginPlay();
    check(InputContext);
    if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        subsystem->AddMappingContext(InputContext, 0);
    }
    
    bShowMouseCursor = true;
    DefaultMouseCursor = EMouseCursor::Default;

    FInputModeGameAndUI inputModeData;    
    inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    inputModeData.SetHideCursorDuringCapture(false);
    SetInputMode(inputModeData);    
}

void ASkirmisherController::SetupInputComponent()
{
    Super::SetupInputComponent();
    USkirmisherInputComponent* skirmisherInputComponent = CastChecked<USkirmisherInputComponent>(InputComponent);

    skirmisherInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ASkirmisherController::ActionMove);
    skirmisherInputComponent->BindAbilityActions(InputConfig, this, &ASkirmisherController::AbilityInputTagPressed,&ASkirmisherController::AbilityInputTagReleased,&ASkirmisherController::AbilityInputTagHeld);
}

void ASkirmisherController::PlayerTick(float DeltaTime)
{
    Super::PlayerTick(DeltaTime);
    CursorTrace();

    AutoRun();
}

void ASkirmisherController::AutoRun()
{
    if (!bAutoRunning) return;

    if (APawn* controlledPawn = GetPawn())
    {
        const FVector locationOnSpline = Spline->FindLocationClosestToWorldLocation(controlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
        const FVector direction = Spline->FindDirectionClosestToWorldLocation(locationOnSpline, ESplineCoordinateSpace::World);
        controlledPawn->AddMovementInput(direction);
        const float distanceToDestination = (locationOnSpline - CachedDestination).Length();
        if (distanceToDestination <= AutoRunAcceptanceRadius)
        {
            bAutoRunning = false;
        }
    }
}



void ASkirmisherController::ActionMove(const FInputActionValue &InputValue)
{
    const FVector2D inputAxisVector = InputValue.Get<FVector2D>();
    const FRotator rotation = GetControlRotation();
    const FRotator yawRotation(0.f, rotation.Yaw, 0.f);
    
    const FVector forwardDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
    const FVector rightDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

    if (APawn* controllPawn = GetPawn<APawn>())
    {
        controllPawn->AddMovementInput(forwardDirection, inputAxisVector.Y);
        controllPawn->AddMovementInput(rightDirection, inputAxisVector.X);
    }

}

void ASkirmisherController::AbilityInputTagPressed(FGameplayTag InputTag)
{
    if (InputTag.MatchesTagExact(FSkirmisherGameplayTags::Get().InputTag_LMB))
    {
        bTargeting = ThisActor ? true : false;
        bAutoRunning = false;
    }  
}
void ASkirmisherController::AbilityInputTagReleased(FGameplayTag InputTag)
{
    if (!InputTag.MatchesTagExact(FSkirmisherGameplayTags::Get().InputTag_LMB))
    {
        if (GetASC())
        {
            GetASC()->AbilityInputTagReleased(InputTag);
        }
        return;
    }
    if (bTargeting)
    {
        if (GetASC())
        {
            GetASC()->AbilityInputTagHeld(InputTag);
        }
    }
    else
    {
        APawn* controlledPawn = GetPawn();
        if (FollowTime <= ShortPressThreshold && controlledPawn)
        {
            if (UNavigationPath* navPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, controlledPawn->GetActorLocation(), CachedDestination))
            {
                Spline->ClearSplinePoints();
                for (const FVector& pointLoc : navPath->PathPoints)
                {
                    Spline->AddSplinePoint(pointLoc, ESplineCoordinateSpace::World);
                    DrawDebugSphere(GetWorld(), pointLoc, 5.f, 8, FColor::Yellow, false, 2.f);
                }
                CachedDestination = navPath->PathPoints[navPath->PathPoints.Num() - 1];
                bAutoRunning = true;
            }
        }
        FollowTime = 0.f;
        bTargeting = false;
    }
}
void ASkirmisherController::AbilityInputTagHeld(FGameplayTag InputTag)
{
    if (!InputTag.MatchesTagExact(FSkirmisherGameplayTags::Get().InputTag_LMB))
    {
        if (GetASC())
        {
            GetASC()->AbilityInputTagHeld(InputTag);
        }
        return;
    }

    if (bTargeting)
    {
        if (GetASC())
        {
            GetASC()->AbilityInputTagHeld(InputTag);
        }
    }
    else
    {
        FollowTime += GetWorld()->GetDeltaSeconds();
        FHitResult hit;
        if (GetHitResultUnderCursor(ECC_Visibility, false, hit))
        {
            CachedDestination = hit.ImpactPoint;
        }

        if (APawn* controlledPawn = GetPawn())
        {
            const FVector worldDirection = (CachedDestination - controlledPawn->GetActorLocation()).GetSafeNormal();
            controlledPawn->AddMovementInput(worldDirection);
        }
    }
}

USkirmisherAbilitySystemComponent* ASkirmisherController::GetASC()
{
    if (SkirmisherAbilitySystemComponent == nullptr)
    {        
        SkirmisherAbilitySystemComponent = Cast<USkirmisherAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
    }
    return SkirmisherAbilitySystemComponent;
}


void ASkirmisherController::CursorTrace()
{
    FHitResult cursorHit;
    GetHitResultUnderCursor(ECC_Visibility, false, cursorHit);
    if (!cursorHit.bBlockingHit) return;
        
    LastActor = ThisActor;
    ThisActor = cursorHit.GetActor();

    /*
    Line trace from cursor. There are several scenarios:
    A. LastActor is null && ThisActor is null
        - Do nothing.
    B. LastActor is null && ThisActor is valid
        - Highlight ThisActor.
    C. LastActor is valid && ThisActor is null
        - UnHighlight LastActor.
    D. Both actor are valid, but LastActor != ThisActor
        - UnHighlight LastActor, and Highlight ThisActor.
    E. Both actor are valid, but LastActor != ThisActor
        - Do nothing.
    */
    if (LastActor == nullptr)
    {
        if (ThisActor != nullptr)
        {
            // Case B
            ThisActor->HighlightActor();
        }
        // Case A
    }
    else // LastActor is valid
    {
        if (ThisActor == nullptr)
        {
            // Case C
            LastActor->UnHighlightActor();
        }
        else
        {
            if (ThisActor != LastActor)
            {
                // Case D
                ThisActor->HighlightActor();
                LastActor->UnHighlightActor();
            }
            // Case E
        }
    }
}