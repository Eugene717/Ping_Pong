// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "P_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class PING_PONG_API AP_GameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AP_GameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;

private:
	void StartGame();

private:
	int32 ConnectedPlayersCount;	
};
