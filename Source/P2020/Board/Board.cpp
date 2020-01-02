// Fill out your copyright notice in the Description page of Project Settings.


#include "Board.h"
#include "Engine/World.h"

// Sets default values
ABoard::ABoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Æ®·£½ºÆû"));
	check(RootComponent);

	world = GetWorld();
	tileSpawnParam.Owner = this;

}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();
}

void ABoard::OnConstruction(const FTransform& Tranform)
{
	Super::OnConstruction(Tranform);
	initializeBoard();
}

// Called every frame
void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TArray<FBoardTileDatatableRow> ABoard::getBoardTiles()
{
	TArray<FBoardTileDatatableRow> boardTileArray;
	FString ContextString;
	TArray<FName> rowNames = BoardTileDataTable->GetRowNames();
	for (auto& rowName : rowNames)
	{
		FBoardTileDatatableRow* row = BoardTileDataTable->FindRow<FBoardTileDatatableRow>(rowName, ContextString);
		if (row)
		{
			boardTileArray.Add(*row);
		}
	}
	return boardTileArray;
}

ATile* ABoard::spawnTile(int index, FBoardTileDatatableRow& row)
{
	FVector location = FVector(
		row.X * TileDistance,
		row.Y * TileDistance,
		row.Height * TileDistance / 3
	);
	FActorSpawnParameters param(tileSpawnParam);
	FString nameStr = FString(TEXT("Tile_")).Append(FString::FromInt(index));
	param.Name = FName(*nameStr);

	ATile* tile = GetWorld()->SpawnActor<ATile>(param);
	tile->SetTileType((ETileType)row.Type);
	tile->SetActorLocation(location + GetActorLocation());

	return tile;
}

void ABoard::initializeBoard()
{
	for (ATile* tile : tiles)
	{
		GetWorld()->DestroyActor(tile, true);
	}
	tiles.Empty();

	TArray<FBoardTileDatatableRow> tilesFromData = getBoardTiles();
	int index = 0;
	for (FBoardTileDatatableRow row : tilesFromData)
	{
		tiles.Add(spawnTile(index, row));
		index++;
	}
}

