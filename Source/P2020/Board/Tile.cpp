// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	mesh->SetStaticMesh(MeshAsset.Object);
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
	FString assetPath = TEXT("MaterialInstanceConstant'/Game/Material/Mat_@TYPE@Tile.Mat_@TYPE@Tile'");
	switch (tileType)
	{
	case ETileType::TE_Water:
		assetPath = assetPath.Replace(TEXT("@TYPE@"), TEXT("Water"));
		break;
	case ETileType::TE_Fire:
		assetPath = assetPath.Replace(TEXT("@TYPE@"), TEXT("Fire"));
		break;
	case ETileType::TE_Desert:
		assetPath = assetPath.Replace(TEXT("@TYPE@"), TEXT("Desert"));
		break;
	case ETileType::TE_Forest:
		assetPath = assetPath.Replace(TEXT("@TYPE@"), TEXT("Forest"));
		break;
	case ETileType::TE_Start:
	case ETileType::TE_SouthCastle:
	case ETileType::TE_NorthCastle:
	case ETileType::TE_WestCastle:
	case ETileType::TE_EastCastle:
		assetPath = assetPath.Replace(TEXT("@TYPE@"), TEXT("Special"));
		break;
	}

	UMaterialInterface* material = LoadObject<UMaterialInterface>(NULL, *assetPath);
	mesh->SetMaterial(0, material);
}


