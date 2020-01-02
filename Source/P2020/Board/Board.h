// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tile.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Board.generated.h"

USTRUCT(BlueprintType)
struct FBoardTileDatatableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
		int32 X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
		int32 Y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
		int32 Height;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
		uint8 Type;
};


UCLASS()
class P2020_API ABoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Tranform) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		int TileDistance = 110;

	UPROPERTY(EditAnywhere)
		UDataTable* BoardTileDataTable = nullptr;

private:
	void initializeBoard();

	TArray<FBoardTileDatatableRow> getBoardTiles();
	ATile* spawnTile(int index, FBoardTileDatatableRow& row);

	UWorld* world = nullptr;
	FActorSpawnParameters tileSpawnParam;
	TArray<ATile*> tiles;

};
