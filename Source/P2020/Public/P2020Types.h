#pragma once

#include "P2020Types.generated.h"

UENUM()
enum class ECardType : uint8
{
	Spell,
	Creature,
	Item
};

USTRUCT()
struct FCard {
	GENERATED_BODY()
public:
	FString Name;
	FString Image;

	ECardType Type;
};

UENUM()
enum class ETileType : uint8
{
	Start UMETA(DisplayName = "Start Tile"),
	Water UMETA(DisplayName = "Water"),
	Fire UMETA(DisplayName = "Fire"),
	Desert UMETA(DisplayName = "Desert"),
	Forest UMETA(DisplayName = "Forest"),
	Neutral UMETA(DisplayName = "Neutral"),
	SouthCastle UMETA(DisplayName = "South Castle"),
	NorthCastle UMETA(DisplayName = "North Castle"),
	EastCastle UMETA(DisplayName = "East Castle"),
	WestCastle UMETA(DisplayName = "West Castle"),
};

UENUM()
enum class LevelState : uint8
{
	Waiting,
	Playing,
	Finished,
};

USTRUCT(BlueprintType)
struct FBoardTileDatatableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
		int32 X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
		int32 Y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
		int32 Height;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
		uint8 Type;
};