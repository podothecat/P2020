#include "RoundGameState.h"
#include "P2020.h"
#include "P2020Marker.h"
#include "P2020Tile.h"
#include "UObject/ConstructorHelpers.h"

ARoundGameState::ARoundGameState()
{
	/*
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("/Game/StageDataTables/testmap1.testmap1"));
	if (DataTable.Succeeded())
	{
		_mapDataTable = DataTable.Object;
	}
	*/
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> matWhite(TEXT("Material'/Game/Material/Mat_SpecialTile.Mat_SpecialTile'"));
	if (matWhite.Succeeded())
	{
		_tileMaterialInstances.Emplace(matWhite.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> matBlack(TEXT("Material'/Game/Material/Mat_BlackTile.Mat_BlackTile'"));
	if (matBlack.Succeeded())
	{
		_tileMaterialInstances.Emplace(matBlack.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> matRed(TEXT("Material'/Game/Material/Mat_FireTile.Mat_FireTile'"));
	if (matRed.Succeeded())
	{
		_tileMaterialInstances.Emplace(matRed.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> matBlue(TEXT("Material'/Game/Material/Mat_WaterTile.Mat_WaterTile'"));
	if (matBlue.Succeeded())
	{
		_tileMaterialInstances.Emplace(matBlue.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> matGreen(TEXT("Material'/Game/Material/Mat_ForestTile.Mat_ForestTile'"));
	if (matGreen.Succeeded())
	{
		_tileMaterialInstances.Emplace(matGreen.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> matYellow(TEXT("Material'/Game/Material/Mat_DesertTile.Mat_DesertTile'"));
	if (matYellow.Succeeded())
	{
		_tileMaterialInstances.Emplace(matYellow.Object);
	}


}

void ARoundGameState::initializeMap() 
{
	UWorld* world = GetWorld();
	
	FString assetName = TEXT("DataTable'/Game/StageDataTables/");
	
	FString mapName = TEXT("testmap1");
	assetName.Append(mapName);
	assetName.Append(TEXT("."));
	assetName.Append(mapName);
	assetName.Append(TEXT("'"));
	
	UDataTable* mapDataTable = LoadObject<UDataTable>(NULL, *assetName, NULL, LOAD_None, NULL);
	TArray<FName> rowNames = mapDataTable->GetRowNames();
	FString ContextString;
	int i = 0;
	int maxX = INT_MIN, maxY = INT_MIN, minX = INT_MAX, minY = INT_MAX;
	for (auto& rowName : rowNames)
	{
		FTileTableRow* row = mapDataTable->FindRow<FTileTableRow>(rowName, ContextString);
		if (row)
		{
			_currentMapData.Add(*row);
			_tiles.Add(SpawnTile(i++, *row));

			if (row->x > maxX) {
				maxX = row->x;
			}
			if (row->y > maxY) {
				maxY = row->y;
			}
			if (row->x < minX) {
				minX = row->x;
			}
			if (row->y < minY) {
				minY = row->y;
			}
		}
	}

	TArray<FVector> Points;
	Points.Add(FVector(maxX * tileDistance, maxY * tileDistance + tileDistance, 0));
	Points.Add(FVector(minX * tileDistance - tileDistance, minY * tileDistance, 0));

	WorldBounds = FBox(Points);
	return;
	/*
	FString assetName = TEXT("DataTable'/Game/StageDataTables/");
	// assetName = assetName.Append(TEXT("Stage1.Stage1'"));
	FString mapName = TEXT("Stage1");
	assetName.Append(mapName);
	assetName.Append(TEXT("."));
	assetName.Append(mapName);
	assetName.Append(TEXT("'"));
	
	// json data 읽어서 _startTile부터 Tree 구성

	UDataTable* mapDataTable = LoadObject<UDataTable>(NULL, *assetName, NULL, LOAD_None, NULL);

	TArray<FBoardTileDatatableRow> boardTileArray;
	FString ContextString;

	TArray<FName> rowNames = mapDataTable->GetRowNames();
	int i = 0;
	int maxX = INT_MIN, maxY = INT_MIN, minX = INT_MAX, minY = INT_MAX;
	for (auto& rowName : rowNames)
	{
		FBoardTileDatatableRow* row = mapDataTable->FindRow<FBoardTileDatatableRow>(rowName, ContextString);
		if (row)
		{
			boardTileArray.Add(*row);
			spawnTile(i++, *row);
			if (row->X > maxX) {
				maxX = row->X;
			}
			if (row->Y > maxY) {
				maxY = row->Y;
			}
			if (row->X < minX) {
				minX = row->X;
			}
			if (row->Y < minY) {
				minY = row->Y;
			}
		}
	}

	TArray<FVector> Points;
	Points.Add(FVector(maxX * tileDistance, maxY * tileDistance + tileDistance, 0));
	Points.Add(FVector(minX * tileDistance - tileDistance, minY * tileDistance, 0));

	WorldBounds = FBox(Points);
	*/
}

void ARoundGameState::InitiateRound(int goalMana, int initialMana, TArray<FP2020Player>& players)
{
	_goalMana = goalMana;
	_initialMana = initialMana;
	_players = players;

	UWorld* world = GetWorld();

	// 맵 생성
	initializeMap();

	// 플레이어가 전부 연결 될 때까지 기다린다
	int index = 0;
	for (FP2020Player player : _players)
	{
		// 마커 스폰
		AP2020Marker* marker = world->SpawnActor<AP2020Marker>();
		marker->Initialize(_startTile);
		player.SetMarker(marker);
	}
}

FP2020Player& ARoundGameState::getNextPlayer() {
	return _players[0];
}

void ARoundGameState::StartRound() 
{
	if (!isGameFinished()) 
	{
		FP2020Player& player = getNextPlayer();
		OnBeginTurn(player);
	}
	else {
		//  게임 끝
	}
}

void ARoundGameState::OnBeginTurn(FP2020Player& player)
{
	FString name = player.GetName();
	// 이번 턴 플레이어 폰에 카메라 이동
	UE_LOG(LogTemp, Log, TEXT("Player %s turn begins"), *name)

	// 카드 뽑기 화면 출력
	UE_LOG(LogTemp, Log, TEXT("Player %s card draw screen"), *name)

	// 해당 유저 보유 아이템 출력
	UE_LOG(LogTemp, Log, TEXT("Player %s card list"), *name)

	player.StartTurn();
}

bool ARoundGameState::isGameFinished() 
{
	return false;
}

AP2020Tile* ARoundGameState::SpawnTile(int index, FTileTableRow& row)
{
	FVector location = FVector(
		row.x * tileDistance,
		row.y * tileDistance,
		row.z * tileDistance / 3
	);

	FString nameStr = FString(TEXT("Tile_") + FString::FromInt(index));

	FActorSpawnParameters SpawnParams;
	SpawnParams.Name = FName(*nameStr);
	// SpawnParams.Owner = this;

	AP2020Tile* tile = GetWorld()->SpawnActor<AP2020Tile>(AP2020Tile::StaticClass(), SpawnParams);
	// tile->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	// tile->SetTileType((ETileType)row.Type);
	tile->SetActorLocation(location);
	tile->SetActorScale3D(FVector(4, 4, 4));

	tile->SetMaterial(_tileMaterialInstances[static_cast<uint8>(row.tileType)]);

	if (row.index == 0)
	{
		_startTile = tile;
	}

	return tile;
}


AP2020Tile* ARoundGameState::spawnTile(int index, FBoardTileDatatableRow& row)
{
	FVector location = FVector(
		row.X * tileDistance,
		row.Y * tileDistance,
		row.Height * tileDistance / 3
	);

	FString nameStr = FString(TEXT("Tile_") + FString::FromInt(index));

	FActorSpawnParameters SpawnParams;
	SpawnParams.Name = FName(*nameStr);
	// SpawnParams.Owner = this;

	AP2020Tile* tile = GetWorld()->SpawnActor<AP2020Tile>(AP2020Tile::StaticClass(), SpawnParams);
	// tile->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	// tile->SetTileType((ETileType)row.Type);
	tile->SetActorLocation(location);
	tile->SetActorScale3D(FVector(4, 4, 4));

	return tile;
}

AP2020Tile* ARoundGameState::GetTile(int idx) const
{
	return _tiles[idx];
}