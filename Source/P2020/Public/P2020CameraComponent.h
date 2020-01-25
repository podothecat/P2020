// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "P2020CameraComponent.generated.h"

/**
 * 
 */
UCLASS(config=Game)
class P2020_API UP2020CameraComponent : public UCameraComponent
{
	GENERATED_UCLASS_BODY()

public:

	// Begin UCameraComponent interface

	virtual void GetCameraView(float DeltaTime, FMinimalViewInfo& DesiredView) override;

	// End UCameraComponent interface

	void OnZoomIn();
	void OnZoomOut();

	void UpdateCameraMovement(const APlayerController* InPlayerController);
	void MoveForward(float Val);
	void MoveRight(float Val);
	void AddNoScrollZone(FBox InCoords);

	/*
	 * CLamp the Camera location.
	 *
	 * @param	InPlayerController	The player controller relative to this component.
	 * @param	OutCameraLocation	Structure to receive the clamped coordinates.
	 */
	void ClampCameraLocation(const APlayerController* InPlayerController, FVector& OutCameraLocation);

	/** The minimum offset of the camera. */
	UPROPERTY(config)
		float MinCameraOffset;

	/** The maximum offset of the camera. */
	UPROPERTY(config)
		float MaxCameraOffset;

	/** The angle to look down on the map. */
	UPROPERTY(config)
		FRotator FixedCameraAngle;

	/** How fast the camera moves around when the mouse is at the edge of the screen. */
	UPROPERTY(config)
		float CameraScrollSpeed;

	/** Size of the area at the edge of the screen that will trigger camera scrolling. */
	UPROPERTY(config)
		uint32 CameraActiveBorder;

	/** Minimum amount of camera zoom (How close we can get to the map). */
	UPROPERTY(config)
		float MinZoomLevel;

	/** Maximum amount of camera zoom (How close we can get to the map). */
	UPROPERTY(config)
		float MaxZoomLevel;

	/** Percentage of minimap where center of camera can be placed. */
	UPROPERTY(config)
		float MiniMapBoundsLimit;

	/** Bounds for camera movement. */
	FBox CameraMovementBounds;

	/** Viewport size associated with camera bounds. */
	FVector2D CameraMovementViewportSize;

	/** If set, camera position will be clamped to movement bounds. */
	UPROPERTY(config)
		uint8 bShouldClampCamera : 1;

	/*
	 * Handle the start of a 'pinch'.
	 *
	 * @param	AnchorPosition1		First Anchor position.
	 * @param	AnchorPosition2		Second Anchor position.
	 * @param	DownTime			Time pressed.
	 */
	void OnPinchStarted(const FVector2D& AnchorPosition1, const FVector2D& AnchorPosition2, float DownTime);

	/** Handle the start of a 'pinch'.
	 *
	 * @param	InputHandler		The unput handler related to this pinch.
	 * @param	AnchorPosition1		First Anchor position.
	 * @param	AnchorPosition2		Second Anchor position.
	 * @param	DownTime			Time pressed
	 */
	// void OnPinchUpdate(class UStrategyInput* InputHandler, const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime);

	/** Set the desired camera position. */
	void SetCameraTarget(const FVector& CameraTarget);

	/** Sets the desired zoom level; clamping if necessary */
	void SetZoomLevel(float NewLevel);

	/*
	 * Handle the start swipe/drag
	 *
	 * @param	SwipePosition		Position the swipe begins at
	 *
	 * @returns	true if the swipe was handled and we begun a swipe/drag
	 */
	bool OnSwipeStarted(const FVector2D& SwipePosition);

	/*
	 * Handle the update of a swipe/drag
	 *
	 * @param	SwipePosition		Position for this update
	 * @returns	true if the swipe was handled and we moved the camera position
	 */
	bool OnSwipeUpdate(const FVector2D& SwipePosition);

	/*
	 * Handle the start swipe/drag
	 *
	 * @param	SwipePosition		Position the swipe ends
	 * @returns	true if the swipe was handled and we ended the swipe/drag
	 */
	bool OnSwipeReleased(const FVector2D& SwipePosition);

	/*
	 * Handle the start swipe/drag
	 *
	 * @param	SwipePosition		Position to check
	 * @returns	true if given coordinates are withing a no-scroll zone
	 */
	bool AreCoordsInNoScrollZone(const FVector2D& SwipePosition);

	/* Reset the swipe/drag */
	void EndSwipeNow();

private:
	/** Return the pawn that owns this component. */
	APawn* GetOwnerPawn();

	/** Return the player controller of the pawn that owns this component. */
	APlayerController* GetPlayerController();

	/* Update the movement bounds of this component. */
	void UpdateCameraBounds(const APlayerController* InPlayerController);

	/* List of zones to exclude from scrolling during the camera movement update. */
	TArray<FBox>	NoScrollZones;

	/** Initial Zoom alpha when starting pinch. */
	float InitialPinchAlpha;

	/** Current amount of camera zoom. */
	float ZoomAlpha;

	/** The initial position of the swipe/drag. */
	FVector StartSwipeCoords;
};
