// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "P_PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
/**
 *
 */
UCLASS()
class PING_PONG_API AP_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AP_PlayerController();

	UFUNCTION(Client, Reliable)
		void ClientStartWaiting();

	UFUNCTION(Client, Reliable)
		void ClientStartPlay();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

private:
	void Move(const struct FInputActionValue& InputActionValue);

private:
	UPROPERTY(EditAnywhere, Category = "Input")
		TObjectPtr<UInputMappingContext> PingPongContext;

	UPROPERTY(EditAnywhere, Category = "Input")
		TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "UI")
		TSubclassOf<UUserWidget> WaitingWidgetClass;

	UPROPERTY()
		TObjectPtr<UUserWidget> WaitingWidget;
};
