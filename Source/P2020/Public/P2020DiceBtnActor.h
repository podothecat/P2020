// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "P2020DiceBtnActor.generated.h"

UCLASS()
class P2020_API AP2020DiceBtnActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AP2020DiceBtnActor();
	
	virtual void NotifyActorOnClicked(FKey PressedButton = EKeys::LeftMouseButton) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnMouseOverBegin(UPrimitiveComponent* TouchedComponent);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* _mesh;
};
