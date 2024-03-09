// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameRules/P_GameMode.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Player/P_PlayerController.h"

AP_GameMode::AP_GameMode()
{
	ConnectedPlayersCount = 0;
	bUseSeamlessTravel = true;
}

void AP_GameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	AP_PlayerController* PlayerController = Cast<AP_PlayerController>(NewPlayer);
	if (PlayerController)
	{
		if (ConnectedPlayersCount == 0)
		{
			PlayerController->ClientStartWaiting();
		}

		ConnectedPlayersCount++;

		if (ConnectedPlayersCount == 2)
		{
			StartGame();
		}
	}
}

void AP_GameMode::StartGame()
{
	AP_PlayerController* PlayerController = Cast<AP_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	PlayerController->ClientStartPlay();

	UObject* Actor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), nullptr, TEXT("/Game/Blueprints/Actors/BP_Ball")));
	UBlueprint* GeneratedBP = Cast<UBlueprint>(Actor);

	GetWorld()->SpawnActor<AActor>(GeneratedBP->GeneratedClass, FVector(0.0f, 0.0f, 150.0f), FRotator());
}
