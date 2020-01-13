// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "P2020Tile.generated.h"

UCLASS()
class P2020_API AP2020Tile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AP2020Tile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public: 

private:
	int _x;
	int _y;
	ETileType _type;

	// tile owner;
	// tile creature;
};
