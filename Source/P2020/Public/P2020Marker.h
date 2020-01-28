// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "P2020Marker.generated.h"

class AP2020Tile;

UCLASS()
class P2020_API AP2020Marker : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AP2020Marker();
	void Initialize(AActor* beginTile);
	void MoveForward();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	AP2020Tile* _tile;
	int _tileIdx;
	UStaticMeshComponent* _mesh;
};
