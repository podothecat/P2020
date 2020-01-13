// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RoundGameMode.generated.h"


UCLASS()
class P2020_API ARoundGameMode : public AGameModeBase
{
	GENERATED_BODY()

	ARoundGameMode();
	virtual void InitGameState() override;
	virtual void RestartPlayer(AController* NewPlayer) override;

	static const FString DifficultyOptionName;
};
