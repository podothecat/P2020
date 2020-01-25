#include "P2020.h"
#include "RoundGameState.h"
#include "P2020Marker.h"
#include "P2020Tile.h"
#include "UObject/ConstructorHelpers.h"

void ARoundGameState::initializeMap() 
{
	UWorld* world = GetWorld();

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
		marker->Initialize(nullptr);
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