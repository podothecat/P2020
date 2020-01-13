#pragma once

#include "P2020Types.h"
#include "P2020Player.generated.h"

USTRUCT()
struct FP2020Player {
	GENERATED_BODY()
	FP2020Player() : _name(TEXT("")), _mana(0), _isAI(true), _deck(TArray<FCard>()) {}
	FP2020Player(const FString& name, const int mana, const bool isAI, const TArray<FCard>& deck)
		: _name(name), _mana(mana), _isAI(isAI), _deck(deck)
	{}

public:
	void StartTurn();

public:
	inline void SetMarker(AActor* marker) { _marker = marker; }
	inline FString GetName() { return _name; }
	void SetName(const FString& name) { _name = name; }
	inline int GetMana() { return _mana; }
	void SetMana(const int mana) { _mana = mana; }
	inline bool IsAI() { return _isAI; }
	void SetIsAI(const bool isAI) { _isAI = isAI; }
	inline const TArray<FCard>& GetDeck() { return _deck; }
	void SetDeck(const TArray<FCard>& deck) { _deck = deck; }


private:
	FString _name;
	int _mana;
	bool _isAI;
	TArray<FCard> _deck;

	AActor* _marker;
};
