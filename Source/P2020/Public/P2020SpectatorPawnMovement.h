// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawnMovement.h"
#include "P2020SpectatorPawnMovement.generated.h"

UCLASS()
class P2020_API UP2020SpectatorPawnMovement : public USpectatorPawnMovement
{
	GENERATED_UCLASS_BODY()
		virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	bool bInitialLocationSet;
	
};
