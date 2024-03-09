// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/P_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Blueprint/UserWidget.h"
#include "Player/P_PlayerPawn.h"

AP_PlayerController::AP_PlayerController()
{
	bReplicates = true;
}

void AP_PlayerController::ClientStartWaiting_Implementation()
{
	check(WaitingWidgetClass);

	WaitingWidget = CreateWidget<UUserWidget>(this, WaitingWidgetClass);

	WaitingWidget->AddToViewport(0);

	DisableInput(this);
}

void AP_PlayerController::ClientStartPlay_Implementation()
{
	WaitingWidget->RemoveFromParent();

	EnableInput(this);
}

void AP_PlayerController::BeginPlay()
{
	Super::BeginPlay();	

	check(PingPongContext);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		Subsystem->AddMappingContext(PingPongContext, 0);
}

void AP_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AP_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AP_PlayerController::Move);
}

void AP_PlayerController::Move(const FInputActionValue& InputActionValue)
{
	const float Scale = InputActionValue.Get<float>();

	if (AP_PlayerPawn* ControlledPawn = GetPawn<AP_PlayerPawn>())
	{
		ControlledPawn->ServerMove(Scale);
	}
}