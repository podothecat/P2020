// Fill out your copyright notice in the Description page of Project Settings.

#include "P2020.h"
#include "P2020PlayerController.h"

ARoundGameMode::ARoundGameMode() 
{
	GameStateClass = ARoundGameState::StaticClass();
	PlayerControllerClass = AP2020PlayerController::StaticClass();
}

void ARoundGameMode::InitGameState()
{
	Super::InitGameState();
	
	ARoundGameState* const gameState = GetGameState<ARoundGameState>();
	if (gameState)
	{
		TArray<FCard> deck;
		TArray<FP2020Player> players;
		for (int i = 0; i < 4; ++i) {
			FString Name = TEXT("test");
			FP2020Player p(Name, 0, i == 0 ? false : true, deck);
			players.Add(p);
		}
		gameState->InitiateRound(5000,1000, players);
		gameState->StartRound();
	}
}

const FString ARoundGameMode::DifficultyOptionName(TEXT("Difficulty"));

void ARoundGameMode::RestartPlayer(AController* NewPlayer)
{
	AActor* const StartSpot = FindPlayerStart(NewPlayer);
	if (StartSpot != nullptr)
	{
		// initialize and start it up
		InitStartSpot(StartSpot, NewPlayer);
		
// 		ARoundPlayerController* const NewPC = Cast<ARoundPlayerController>(NewPlayer);
//		if (NewPC != nullptr)
//		{
//			NewPC->SetInitialLocationAndRotation(StartSpot->GetActorLocation(), StartSpot->GetActorRotation());
//		}
	}
	else
	{
// 		UE_LOG(LogGame, Warning, TEXT("Player start not found, failed to restart player"));
	}
}