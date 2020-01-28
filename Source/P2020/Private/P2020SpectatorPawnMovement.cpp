// Fill out your copyright notice in the Description page of Project Settings.

#include "P2020SpectatorPawnMovement.h"
#include "P2020.h"
#include "P2020PlayerController.h"
#include "P2020SpectatorPawn.h"
#include "P2020CameraComponent.h"


UP2020SpectatorPawnMovement::UP2020SpectatorPawnMovement(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), bInitialLocationSet(false)
{
	MaxSpeed = 16000.f;
	Acceleration = 5000.f;
	Deceleration = 4000.f;
}


void UP2020SpectatorPawnMovement::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent)
	{
		return;
	}

	AP2020PlayerController* PlayerController = Cast<AP2020PlayerController>(PawnOwner->GetController());
	if (PlayerController && PlayerController->IsLocalController())
	{
		if (!bInitialLocationSet)
		{
			PawnOwner->SetActorRotation(PlayerController->GetControlRotation());
			PawnOwner->SetActorLocation(PlayerController->GetSpawnLocation());
			bInitialLocationSet = true;
		}

		FVector MyLocation = UpdatedComponent->GetComponentLocation();
		AP2020SpectatorPawn* SpectatorPawn = Cast<AP2020SpectatorPawn>(PlayerController->GetSpectatorPawn());
		if ((SpectatorPawn != NULL) && (SpectatorPawn->GetP2020CameraComponent() != NULL))
		{
			SpectatorPawn->GetP2020CameraComponent()->ClampCameraLocation(PlayerController, MyLocation);
		}
		UpdatedComponent->SetWorldLocation(MyLocation, false);
	}
}

