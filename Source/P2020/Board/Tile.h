// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UENUM()
enum class ETileType : uint8
{
	TE_Start UMETA(DisplayName = "Start Tile"),
	TE_Water UMETA(DisplayName = "Water"),
	TE_Fire UMETA(DisplayName = "Fire"),
	TE_Desert UMETA(DisplayName = "Desert"),
	TE_Forest UMETA(DisplayName = "Forest"),
	TE_Neutral UMETA(DisplayName = "Neutral"),
	TE_SouthCastle UMETA(DisplayName = "South Castle"),
	TE_NorthCastle UMETA(DisplayName = "North Castle"),
	TE_EastCastle UMETA(DisplayName = "East Castle"),
	TE_WestCastle UMETA(DisplayName = "West Castle"),
};

UCLASS()
class P2020_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	   
	void SetTileType(ETileType tileType);

private:
	UStaticMeshComponent* mesh;
	ETileType tileType;
	void updateMaterialByTileType();
};
