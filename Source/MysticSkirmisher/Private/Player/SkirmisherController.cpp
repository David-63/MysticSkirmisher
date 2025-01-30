// Copyright David-6


#include "Player/SkirmisherController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

ASkirmisherController::ASkirmisherController()
{
    bReplicates = true;
}

void ASkirmisherController::BeginPlay()
{
    Super::BeginPlay();
    check(InputContext);
    UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
        
    check(subsystem);
    subsystem->AddMappingContext(InputContext, 0);

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
    UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

    enhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ThisClass::ActionMove);
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
