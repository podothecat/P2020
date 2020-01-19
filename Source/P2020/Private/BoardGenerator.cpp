// Fill out your copyright notice in the Description page of Project Settings.

#include "P2020.h"
#include "BoardGenerator.h"

BoardGenerator::BoardGenerator(const FString& mapName)
{
	FString assetName = TEXT("DataTable'/Game/StageDataTables/");
	// assetName = assetName.Append(TEXT("Stage1.Stage1'"));

	assetName.Append(mapName);
	assetName.Append(TEXT("."));
	assetName.Append(mapName);
	assetName.Append(TEXT("'"));

	// UDataTable* mapDataTable;
	//static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*assetName);
	//if (DataTable.Succeeded())
	{
	//	mapDataTable = DataTable.Object;
	}

	// TArray<FBoardTileDatatableRow> boardTileArray;
	// FString ContextString;

	//if (BoardTileDataTable == nullptr) {
	//	return TArray<FBoardTileDatatableRow>();
	//}
	/*
	TArray<FName> rowNames = BoardTileDataTable->GetRowNames();
	for (auto& rowName : rowNames)
	{
		FBoardTileDatatableRow* row = BoardTileDataTable->FindRow<FBoardTileDatatableRow>(rowName, ContextString);
		if (row)
		{
			boardTileArray.Add(*row);
		}
	}
	return boardTileArray;*/
}

BoardGenerator::~BoardGenerator()
{
}
