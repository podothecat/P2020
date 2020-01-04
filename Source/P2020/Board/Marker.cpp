// Fill out your copyright notice in the Description page of Project Settings.


#include "Marker.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AMarker::AMarker()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cone"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'"));
	mesh->SetStaticMesh(MeshAsset.Object);
	
}

// Called when the game starts or when spawned
void AMarker::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMarker::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	FString assetPath = TEXT("MaterialInstanceConstant'/Game/Material/Mat_WaterTile.Mat_WaterTile'");	
	UMaterialInterface* material = LoadObject<UMaterialInterface>(NULL, *assetPath);
	mesh->SetMaterial(0, material);
}

