// Fill out your copyright notice in the Description page of Project Settings.

#include "P2020.h"
#include "P2020Marker.h"
#include "P2020Tile.h"

// Sets default values
AP2020Marker::AP2020Marker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AP2020Marker::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AP2020Marker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AP2020Marker::Initialize(AActor* beginTile) {
	AP2020Tile* tile = Cast<AP2020Tile>(beginTile);
	if (tile) {
		_tile = tile;
	}
	else {
		//crash
	}
}