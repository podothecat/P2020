#pragma once

#include "P2020Types.h"
#include "P2020Player.h"
#include "RoundGameState.generated.h"

/**
 * 
 */
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
private:
    bool isGameFinished();
    FP2020Player& getNextPlayer();
private:
    int _initialMana;
    int _goalMana;
    TArray<FP2020Player> _players;

    FP2020Player _currentTurnPlayer;
};
