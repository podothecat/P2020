#include "P2020.h"
#include "RoundGameState.h"
#include "P2020Marker.h"

void ARoundGameState::InitiateRound(int goalMana, int initialMana, TArray<FP2020Player>& players)
{
	_goalMana = goalMana;
	_initialMana = initialMana;
	_players = players;

	// 플레이어가 전부 연결 될 때까지 기다린다
	int index = 0;
	UWorld* world = GetWorld();
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