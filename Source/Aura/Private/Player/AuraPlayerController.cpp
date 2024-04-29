// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interface/EnemyInterface.h"
//#include "Engine/LocalPlayer.h"
//#include "GameFramework/Pawn.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	PrevActor = nullptr;
	CurrActor = nullptr;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
	
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	if (HitResult.bBlockingHit)
	{
		// Update Traced actors status
		PrevActor = CurrActor;
		CurrActor = Cast<IEnemyInterface>(HitResult.GetActor());

		/** Cases:
		* 1. prev == nullptr, curr == nullptr.     -- Do nothing
		* 4. prev == valid,   curr == valid.       Same actor   -- Do nothing
		*
		* 2. prev == nullptr, curr == valid.       -- Call Highlight() on curr
		* 3. prev == valid,   curr == nullptr.     -- Call Unhighlight() on prev
		* 5. prev == valid,   curr == valid.       Different actors  -- Call Unhighlight() on prev, call Highlight() on curr
		*/
		if (PrevActor != CurrActor)
		{
			if (PrevActor)
			{
				PrevActor->UnHighlightActor();
			}
			if (CurrActor)
			{
				CurrActor->HighlightActor();
			}
		}
	}
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(InputContext);

	UEnhancedInputLocalPlayerSubsystem* System = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(System);
	System->AddMappingContext(InputContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComp = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComp->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D InputValue = Value.Get<FVector2D>();
	const FRotator Rotation = FRotator(0.f, GetControlRotation().Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControllerPawn = GetPawn<APawn>())
	{
		ControllerPawn->AddMovementInput(ForwardDirection, InputValue.Y);
		ControllerPawn->AddMovementInput(RightDirection, InputValue.X);
	}
}