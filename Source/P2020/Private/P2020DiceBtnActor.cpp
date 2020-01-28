// Fill out your copyright notice in the Description page of Project Settings.


#include "P2020DiceBtnActor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"
#include "P2020PlayerController.h"
#include "RoundGameState.h"
// Sets default values
AP2020DiceBtnActor::AP2020DiceBtnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshOb_Cube(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));
	_mesh->SetStaticMesh(StaticMeshOb_Cube.Object);
	_mesh->SetupAttachment(RootComponent);
	_mesh->OnBeginCursorOver.AddDynamic(this, &AP2020DiceBtnActor::OnMouseOverBegin);
	
}


void AP2020DiceBtnActor::OnMouseOverBegin(UPrimitiveComponent* TouchedComponent)
{
	UE_LOG(LogTemp, Log, TEXT("MouseOver"));
}

void AP2020DiceBtnActor::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);
	Cast<ARoundGameState>(GetWorld()->GetGameState())->OnRoleDice();
}

// Called when the game starts or when spawned
void AP2020DiceBtnActor::BeginPlay()
{
	Super::BeginPlay();
	EnableInput(GetWorld()->GetFirstPlayerController());
}

// Called every frame
void AP2020DiceBtnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

