// Fill out your opyright notice in the Description page of Project Settings.


#include "Board.h"
#include "Engine/World.h"

// Sets default values
ABoard::ABoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Ʈ������"));
	check(RootComponent);

}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();
}

void ABoard::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	//Get the name of the property that was changed  
	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(ABoard, BoardTileDataTable))
	{
		isInitialized = false;
		initializeBoard();
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
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
	
	if (BoardTileDataTable == nullptr) {
		return TArray<FBoardTileDatatableRow>();
	}

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

	FString nameStr = FString(TEXT("Tile_") + FString::FromInt(index));
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Name = FName(*nameStr);
	SpawnParams.Owner = this;

	ATile* tile = GetWorld()->SpawnActor<ATile>(ATile::StaticClass(), SpawnParams);
	tile->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	tile->SetTileType((ETileType)row.Type);
	tile->SetActorLocation(location + GetActorLocation());

	return tile;
}

void ABoard::initializeBoard()
{
	if (!isInitialized) 
	{
		for (ATile* tile : tiles)
		{
			tile->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
			tile->Destroy();
		}
		tiles.Empty();


		if (Debug) return;
		TArray<FBoardTileDatatableRow> tilesFromData = getBoardTiles();
		
		if (tilesFromData.Num() < 1 )
		{
			return;
		}

		int index = 0;
		for (FBoardTileDatatableRow row : tilesFromData)
		{
			ATile* tile = spawnTile(index, row);
			tiles.Add(tile);
			index++;
		}

		isInitialized = true;
	}
}

