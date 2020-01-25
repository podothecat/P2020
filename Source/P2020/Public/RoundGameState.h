#pragma once

#include "P2020Types.h"
#include "P2020Player.h"
#include "RoundGameState.generated.h"

class AP2020Tile;

UCLASS()
class P2020_API ARoundGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
    void InitiateRound(int goalMana, int initialMana, TArray<FP2020Player>& players);
    void StartRound();

    void OnBeginTurn(FP2020Player& player);

    void OnSelectSpell();
    void OnRoleDice();

    FBox WorldBounds;
private:
    bool isGameFinished();
    FP2020Player& getNextPlayer();
    void initializeMap();
    // TArray<FBoardTileDatatableRow> getBoardTiles();
    AP2020Tile* spawnTile(int index, FBoardTileDatatableRow& row);
private:
    int _initialMana;
    int _goalMana;
    TArray<FP2020Player> _players;
    AActor* _startTile;

    FP2020Player _currentTurnPlayer;

    const int tileDistance = 500;
};
