// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "P2020PlayerController.generated.h"

class AP2020SpectatorPawn;
class UP2020CameraComponent;
/**
 * 
 */
UCLASS()
class P2020_API AP2020PlayerController : public APlayerController
{
	GENERATED_UCLASS_BODY()

public:
	// Begin PlayerController interface
	/** fixed rotation */
	virtual void UpdateRotation(float DeltaTime) override;

protected:
	/** update input detection */
	virtual void ProcessPlayerInput(const float DeltaTime, const bool bGamePaused) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

public:

	/** set desired camera position. */
	void SetCameraTarget(const FVector& CameraTarget);

	/** helper function to toggle input detection. */
	void SetIgnoreInput(bool bIgnore);

	/** Input handlers. */
	void OnTapPressed(const FVector2D& ScreenPosition, float DownTime);
	void OnHoldPressed(const FVector2D& ScreenPosition, float DownTime);
	void OnHoldReleased(const FVector2D& ScreenPosition, float DownTime);
	void OnSwipeStarted(const FVector2D& AnchorPosition, float DownTime);
	void OnSwipeUpdate(const FVector2D& ScreenPosition, float DownTime);
	void OnSwipeReleased(const FVector2D& ScreenPosition, float DownTime);
	void OnSwipeTwoPointsStarted(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime);
	void OnSwipeTwoPointsUpdate(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime);
	void OnPinchStarted(const FVector2D& AnchorPosition1, const FVector2D& AnchorPosition2, float DownTime);
	void OnPinchUpdate(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime);

	/** Toggles the ingame menu display. */
	// void OnToggleInGameMenu();
protected:
	/** if set, input and camera updates will be ignored */
	uint8 bIgnoreInput : 1;

	/** currently selected actor */
	TWeakObjectPtr<AActor> SelectedActor;

	/** Swipe anchor. */
	FVector SwipeAnchor3D;

	FVector2D PrevSwipeScreenPosition;

	/** Previous swipe mid point. */
	FVector2D PrevSwipeMidPoint;

	/** Custom input handler. */
	//UPROPERTY()
	//	class UStrategyInput* InputHandler;

	/**
	 * Change current selection (on toggle on the same).
	 *
	 * @param	NewFocus	Actor to focus on.
	 * @param	NewPosition
	 */
	void SetSelectedActor(AActor* NewFocus, const FVector& NewPosition);

	/**
	 * Get friendly target under screen space coordinates.
	 *
	 * @param	ScreenPoint	Screen coordinates to check
	 * @param	WorldPoint	Point in the world the screen coordinates projected onto.
	 */
	AActor* GetFriendlyTarget(const FVector2D& ScreenPoint, FVector& WorldPoint) const;

	/**
	 * Get audio listener position and orientation.
	 *
	 * @param
	 * @param
	 * @param
	 */
	// virtual void GetAudioListenerPosition(FVector& Location, FVector& FrontDir, FVector& RightDir) override;

private:
	/** Helper to return cast version of Spectator pawn. */
	AP2020SpectatorPawn* GetP2020SpectatorPawn() const;

	/** Helper to return camera component via spectator pawn. */
	UP2020CameraComponent* GetCameraComponent() const;
};
