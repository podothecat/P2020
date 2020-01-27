// Fill out your copyright notice in the Description page of Project Settings.

#include "P2020Marker.h"
#include "P2020.h"
#include "P2020Tile.h"
#include "AIController.h"

// Sets default values
AP2020Marker::AP2020Marker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshOb_Cube(TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'"));
	_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));
	_mesh->SetStaticMesh(StaticMeshOb_Cube.Object);
	RootComponent = _mesh;
}

// Called when the game starts or when spawned
void AP2020Marker::BeginPlay()
{
	Super::BeginPlay();

	//For Test
	MoveForward();
}

// Called every frame
void AP2020Marker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AP2020Marker::Initialize(AActor* beginTile) {
	constexpr int StartTileIdx = 0;

	AP2020Tile* tile = Cast<AP2020Tile>(beginTile);
	if (tile) {
		_tile = tile;
		_tileIdx = StartTileIdx;

		FVector pos = _tile->GetActorLocation();
		pos.Z += 250.f;
		RootComponent->SetWorldLocation(pos);
	}
	else {
		//crash
	}
}

void AP2020Marker::MoveForward()
{
	
	ARoundGameState* const state = GetWorld()->GetGameState<ARoundGameState>();
	//임시로 교차로 없이 다음으로 설정
	_tileIdx = (_tileIdx + 1) % 20;

	_tile = state->GetTile(_tileIdx);

	//동작을 안한다. 담에보는걸로
	Cast<AAIController>(GetController())->MoveToActor(_tile);

}