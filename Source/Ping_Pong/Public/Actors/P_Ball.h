// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "P_Ball.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class PING_PONG_API AP_Ball : public AActor
{
	GENERATED_BODY()
	
public:	
	AP_Ball();

	virtual void BeginPlay() override;

private:
	void SetRandomDirection();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<USphereComponent> SphereCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UStaticMeshComponent> Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UProjectileMovementComponent> MovementComponent;

};
