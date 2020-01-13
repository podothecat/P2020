#include "P2020.h"
#include "RoundGameState.h"
#include "P2020Marker.h"

void ARoundGameState::InitiateRound(int goalMana, int initialMana, TArray<FP2020Player>& players)
{
	_goalMana = goalMana;
	_initialMana = initialMana;
	_players = players;

	// �÷��̾ ���� ���� �� ������ ��ٸ���
	int index = 0;
	UWorld* world = GetWorld();
	for (FP2020Player player : _players)
	{
		// ��Ŀ ����
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
		//  ���� ��
	}
}

void ARoundGameState::OnBeginTurn(FP2020Player& player)
{
	FString name = player.GetName();
	// �̹� �� �÷��̾� ���� ī�޶� �̵�
	UE_LOG(LogTemp, Log, TEXT("Player %s turn begins"), *name)

	// ī�� �̱� ȭ�� ���
	UE_LOG(LogTemp, Log, TEXT("Player %s card draw screen"), *name)

	// �ش� ���� ���� ������ ���
	UE_LOG(LogTemp, Log, TEXT("Player %s card list"), *name)

	player.StartTurn();
}

bool ARoundGameState::isGameFinished() 
{
	return false;
}