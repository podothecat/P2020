// Fill out your copyright notice in the Description page of Project Settings.

#include "P2020SpectatorPawn.h"
#include "P2020.h"
#include "P2020SpectatorPawnMovement.h"
#include "P2020CameraComponent.h"


AP2020SpectatorPawn::AP2020SpectatorPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UP2020SpectatorPawnMovement>(Super::MovementComponentName))
{
	GetCollisionComponent()->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	bAddDefaultMovementBindings = false;
	P2020CameraComponent = CreateDefaultSubobject<UP2020CameraComponent>(TEXT("P2020CameraComponent"));
}

	
void AP2020SpectatorPawn::MoveForward(float Val)
{
	P2020CameraComponent->MoveForward(Val);
}

void AP2020SpectatorPawn::MoveRight(float Val)
{
	P2020CameraComponent->MoveRight(Val);
}

void AP2020SpectatorPawn::SetupPlayerInputComponent(class UInputComponent* playerInputComponent)
{
	check(playerInputComponent);

	playerInputComponent->BindAction("ZoomOut", IE_Pressed, this, &AP2020SpectatorPawn::OnMouseScrollUp);
	playerInputComponent->BindAction("ZoomIn", IE_Pressed, this, &AP2020SpectatorPawn::OnMouseScrollDown);

	playerInputComponent->BindAxis("MoveForward", this, &AP2020SpectatorPawn::MoveForward);
	playerInputComponent->BindAxis("MoveRight", this, &AP2020SpectatorPawn::MoveRight);
}

void AP2020SpectatorPawn::OnMouseScrollUp()
{
}

void AP2020SpectatorPawn::OnMouseScrollDown()
{
}


UP2020CameraComponent* AP2020SpectatorPawn::GetP2020CameraComponent() {
	check(P2020CameraComponent != NULL);
	return P2020CameraComponent;
}