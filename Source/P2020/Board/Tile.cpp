// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	mesh->SetStaticMesh(MeshAsset.Object);
	RootComponent = mesh;

	mesh->SetMaterial(0, nullptr);

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::SetTileType(ETileType type)
{
	tileType = type;
	updateMaterialByTileType();
}

void ATile::updateMaterialByTileType()
{
	switch (tileType)
	{
	case ETileType::TE_Start:
		break;
	case ETileType::TE_Water:
		break;
	case ETileType::TE_Fire:
		break;
	case ETileType::TE_Desert:
		break;
	case ETileType::TE_Forest:
		break;
	case ETileType::TE_SouthCastle:
	case ETileType::TE_NorthCastle:
	case ETileType::TE_WestCastle:
	case ETileType::TE_EastCastle:

		break;
	}

	// LoadObject(NULL, TEXT("/Game/"))

	// static ConstructorHelpers::FObjectFinder<UMaterial>materialAsset(LOCTEXT("/Game/Material/Mat_", "DesertTile"));
}


