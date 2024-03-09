// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/P_Ball.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AP_Ball::AP_Ball()
{
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("BoxCollision"));
	RootComponent = SphereCollision;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(RootComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = RootComponent;

	NetUpdateFrequency = 100;
	bReplicates = true;
}

void AP_Ball::BeginPlay()
{
	Super::BeginPlay();
	
	SetReplicateMovement(true);

	SetRandomDirection();
}

void AP_Ball::SetRandomDirection()
{
	FVector Vector;

	if (FMath::RandBool())
		Vector.X = 2000.0f;
	else
		Vector.X = -2000.0f;

	if (FMath::RandBool())
		Vector.Y = 2000.0f;
	else
		Vector.Y = 2000.0f;

	Vector.Z = 0.0f;

	MovementComponent->SetVelocityInLocalSpace(Vector);
}

