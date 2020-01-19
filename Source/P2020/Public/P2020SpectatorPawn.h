// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "P2020SpectatorPawn.generated.h"


class UP2020CameraComponent;
/**
 * 
 */
UCLASS()
class P2020_API AP2020SpectatorPawn : public ASpectatorPawn
{
	GENERATED_UCLASS_BODY()
public:
	virtual void MoveForward(float Val) override;
	virtual void MoveRight(float Val) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
private:
	UPROPERTY(Category = CameraActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UP2020CameraComponent* P2020CameraComponent;
public:
	void OnMouseScrollUp();
	void OnMouseScrollDown();
	UP2020CameraComponent* GetP2020CameraComponent();
};
