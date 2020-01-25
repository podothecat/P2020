// Fill out your copyright notice in the Description page of Project Settings.

#include "P2020.h"
#include "P2020Tile.h"

// Sets default values
AP2020Tile::AP2020Tile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	mesh->SetStaticMesh(MeshAsset.Object);
}

// Called when the game starts or when spawned
void AP2020Tile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AP2020Tile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

