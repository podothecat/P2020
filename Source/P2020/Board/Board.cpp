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

	FString nameStr = FString(TEXT("Tile_")).Append(FString::FromInt(index));
	FActorSpawnParameters param;
	param.Name = FName(*nameStr);
	param.Owner = this;

	UChildActorComponent* component = NewObject<UChildActorComponent>(this);
	component->bEditableWhenInherited = true;
	component->RegisterComponent();
	component->SetChildActorClass(ATile::StaticClass());
	component->CreateChildActor();
	
	ATile* tile = (ATile*)component->GetChildActor();
	tile->SetTileType((ETileType)row.Type);
	tile->SetActorLocation(location + GetActorLocation());

	return tile;
}

void ABoard::initializeBoard()
{
	if (!isInitialized) {
		TArray<FBoardTileDatatableRow> tilesFromData = getBoardTiles();
		int index = 0;
		for (FBoardTileDatatableRow row : tilesFromData)
		{
			spawnTile(index, row);
			index++;
		}
		isInitialized = true;
	}
}

