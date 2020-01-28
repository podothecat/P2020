#pragma once

#include "P2020Types.h"
#include "P2020Player.h"
#include "RoundGameState.generated.h"

UENUM()
enum class TileMaterialType : uint8
{
	White, Blck, Red, Blue, Green, Yellow,
};

USTRUCT(BlueprintType)
struct FTileTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
		int index; 				// ÀÎµ¦½º 0ºÎÅÍ Âß ´Ã¾î³­´Ù
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
		int x;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
		int y;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
		int z;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
		int nextIndex1; 	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
		int nextIndex2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
		int nextIndex3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
		TileMaterialType tileType;
};


class AP2020Tile;
class UMaterialInstance;
class AP2020Marker;

UCLASS()
class P2020_API ARoundGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	ARoundGameState();

    void InitiateRound(int goalMana, int initialMana, TArray<FP2020Player>& players);
    void StartRound();

    void OnBeginTurn(FP2020Player& player);

    void OnSelectSpell();
    void OnRoleDice();

    FBox WorldBounds;

	AP2020Tile* GetTile(int idx) const;
private:
    bool isGameFinished();
    FP2020Player& getNextPlayer();
    void initializeMap();
    // TArray<FBoardTileDatatableRow> getBoardTiles();
    AP2020Tile* spawnTile(int index, FBoardTileDatatableRow& row);
	AP2020Tile* SpawnTile(int index, FTileTableRow& row);
private:
    int _initialMana;
    int _goalMana;
    TArray<FP2020Player> _players;
	TArray<AP2020Marker*> _markers;
    AActor* _startTile;

    FP2020Player _currentTurnPlayer;

	TArray<FTileTableRow> _currentMapData;
	TArray<UMaterialInstance*> _tileMaterialInstances;
	TArray<AP2020Tile*> _tiles;

    const int tileDistance = 500;
};
