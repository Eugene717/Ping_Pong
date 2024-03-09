// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/P_PlayerPawn.h"

#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"

AP_PlayerPawn::AP_PlayerPawn()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;
	BoxCollision->SetSimulatePhysics(true);
	BoxCollision->SetEnableGravity(false);

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(RootComponent);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 1500.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);
	Camera->SetRelativeRotation(FRotator(320.0f, 0.0f, 0.0f));

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = RootComponent;
	MovementComponent->MaxSpeed = 3000;

	NetUpdateFrequency = 1000;
}

void AP_PlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	CameraBoom->SetWorldLocationAndRotation(FVector(GetActorLocation().X, GetActorLocation().Y, 1900.0f), BoxCollision->GetComponentRotation());
}

void AP_PlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AP_PlayerPawn::Move(float Scale)
{
	ServerMove(Scale);
}

bool AP_PlayerPawn::ServerMove_Validate(float Scale)
{
	return true;
}

void AP_PlayerPawn::ServerMove_Implementation(float Scale)
{
	BroadcastMove(Scale);
}

void AP_PlayerPawn::BroadcastMove_Implementation(float Scale)
{
	AddActorLocalOffset(FVector(0.0f, 15 * Scale, 0.0f), true);
}
