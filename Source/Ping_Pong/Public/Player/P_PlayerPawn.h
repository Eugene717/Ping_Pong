// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "P_PlayerPawn.generated.h"

class UBoxComponent;
class USpringArmComponent;
class UFloatingPawnMovement;
class UCameraComponent;

UCLASS()
class PING_PONG_API AP_PlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	AP_PlayerPawn();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void Move(float Scale);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerMove(float Scale);
	void ServerMove_Implementation(float Scale);
	bool ServerMove_Validate(float Scale);

	UFUNCTION(NetMulticast, Reliable)
		void BroadcastMove(float Scale);
	void BroadcastMove_Implementation(float Scale);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UBoxComponent> BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UStaticMeshComponent> Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UFloatingPawnMovement> MovementComponent;

	FVector CameraPosition;
};
