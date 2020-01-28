// Fill out your copyright notice in the Description page of Project Settings.

#include "P2020PlayerController.h"
#include "P2020.h"
#include "P2020CameraComponent.h"
#include "P2020SpectatorPawn.h"


AP2020PlayerController::AP2020PlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bIgnoreInput(false)
{
	// CheatClass = UP2020CheatManager::StaticClass();
	PrimaryActorTick.bCanEverTick = true;
	SetHidden(false);
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void AP2020PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	/*
	InputHandler = NewObject<UP2020Input>(this);

	BIND_1P_ACTION(InputHandler, EGameKey::Tap, IE_Pressed, &AP2020PlayerController::OnTapPressed);
	BIND_1P_ACTION(InputHandler, EGameKey::Hold, IE_Pressed, &AP2020PlayerController::OnHoldPressed);
	BIND_1P_ACTION(InputHandler, EGameKey::Hold, IE_Released, &AP2020PlayerController::OnHoldReleased);
	BIND_1P_ACTION(InputHandler, EGameKey::Swipe, IE_Pressed, &AP2020PlayerController::OnSwipeStarted);
	BIND_1P_ACTION(InputHandler, EGameKey::Swipe, IE_Repeat, &AP2020PlayerController::OnSwipeUpdate);
	BIND_1P_ACTION(InputHandler, EGameKey::Swipe, IE_Released, &AP2020PlayerController::OnSwipeReleased);
	BIND_2P_ACTION(InputHandler, EGameKey::SwipeTwoPoints, IE_Pressed, &AP2020PlayerController::OnSwipeTwoPointsStarted);
	BIND_2P_ACTION(InputHandler, EGameKey::SwipeTwoPoints, IE_Repeat, &AP2020PlayerController::OnSwipeTwoPointsUpdate);
	BIND_2P_ACTION(InputHandler, EGameKey::Pinch, IE_Pressed, &AP2020PlayerController::OnPinchStarted);
	BIND_2P_ACTION(InputHandler, EGameKey::Pinch, IE_Repeat, &AP2020PlayerController::OnPinchUpdate);

	FInputActionBinding& ToggleInGameMenuBinding = InputComponent->BindAction("InGameMenu", IE_Pressed, this, &AP2020PlayerController::OnToggleInGameMenu);
	ToggleInGameMenuBinding.bExecuteWhenPaused = true;
	*/
}
/*
void AP2020PlayerController::GetAudioListenerPosition(FVector& OutLocation, FVector& OutFrontDir, FVector& OutRightDir)
{
	Super::GetAudioListenerPosition(OutLocation, OutFrontDir, OutRightDir);

	ARoundGameState const* const MyGameState = GetWorld()->GetGameState<ARoundGameState>();
	if (GEngine && GEngine->GameViewport && GEngine->GameViewport->ViewportFrame && MyGameState != NULL && MyGameState->MiniMapCamera.IsValid())
	{
		// Set Listener position to be the center of the viewport, projected into the game world.

		FViewport* const Viewport = GEngine->GameViewport->ViewportFrame->GetViewport();
		if (Viewport)
		{
			FVector2D const ScreenRes = Viewport->GetSizeXY();

			//float GroundLevel = MyGameState->MiniMapCamera->AudioListenerGroundLevel;
			//const FPlane GroundPlane = FPlane(FVector(0, 0, GroundLevel), FVector::UpVector);
			ULocalPlayer* const MyPlayer = Cast<ULocalPlayer>(Player);

			// @todo: once PlayerCamera is back in, we can just get the ray origin and dir from that instead of
			// needing to deproject. will be much simpler.
			FVector RayOrigin, RayDirection;
			FVector2D const ScreenCenterPoint = ScreenRes * 0.5f;
			FP2020Helpers::DeprojectScreenToWorld(ScreenCenterPoint, MyPlayer, RayOrigin, RayDirection);

			FVector const WorldPoint = FP2020Helpers::IntersectRayWithPlane(RayOrigin, RayDirection, GroundPlane);
			FVector const AudioListenerOffset = MyGameState->MiniMapCamera->AudioListenerLocationOffset;
			OutLocation = WorldPoint.GetClampedToSize(MyGameState->WorldBounds.Min.GetMin(), MyGameState->WorldBounds.Max.GetMax()) + AudioListenerOffset;

			bool bUseCustomOrientation = MyGameState->MiniMapCamera->bUseAudioListenerOrientation;
			if (bUseCustomOrientation)
			{
				OutFrontDir = MyGameState->MiniMapCamera->AudioListenerFrontDir;
				OutRightDir = MyGameState->MiniMapCamera->AudioListenerRightDir;
			}
		}
	}
}*/
/*
void AP2020PlayerController::OnToggleInGameMenu()
{
	AP2020HUD* const P2020HUD = Cast<AP2020HUD>(GetHUD());
	if (P2020HUD)
	{
		P2020HUD->TogglePauseMenu();
	}
}
*/
void AP2020PlayerController::UpdateRotation(float DeltaTime)
{
	FRotator ViewRotation(0, 0, 0);
	FRotator DeltaRot(0, 0, 0);

	if (PlayerCameraManager)
	{
		PlayerCameraManager->ProcessViewRotation(DeltaTime, ViewRotation, DeltaRot);
	}

	SetControlRotation(ViewRotation);
}

void AP2020PlayerController::ProcessPlayerInput(const float DeltaTime, const bool bGamePaused)
{
	// if (!bGamePaused && PlayerInput && InputHandler && !bIgnoreInput)
	{
		// InputHandler->UpdateDetection(DeltaTime);
	}

	Super::ProcessPlayerInput(DeltaTime, bGamePaused);

	if (!bIgnoreInput)
	{
		const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
		AP2020SpectatorPawn* P2020Pawn = GetP2020SpectatorPawn();
		if ((P2020Pawn != NULL) && (LocalPlayer != NULL))
		{
			P2020Pawn->GetP2020CameraComponent()->UpdateCameraMovement(this);
		}
	}
}

void AP2020PlayerController::SetCameraTarget(const FVector& CameraTarget)
{
	if (GetCameraComponent() != NULL)
	{
		GetCameraComponent()->SetCameraTarget(CameraTarget);
	}
}
/*
AActor* AP2020PlayerController::GetFriendlyTarget(const FVector2D& ScreenPoint, FVector& WorldPoint) const
{
	FHitResult Hit;
	if (GetHitResultAtScreenPosition(ScreenPoint, COLLISION_WEAPON, true, Hit))
	{
		if (!AP2020GameMode::OnEnemyTeam(Hit.GetActor(), this))
		{
			WorldPoint = Hit.ImpactPoint;
			return Hit.GetActor();
		}
	}

	return NULL;
}*/

void AP2020PlayerController::SetIgnoreInput(bool bIgnore)
{
	bIgnoreInput = bIgnore;
}

/*
uint8 AP2020PlayerController::GetTeamNum() const
{
	return EP2020Team::Player;
};

void AP2020PlayerController::SetSelectedActor(AActor* NewSelectedActor, const FVector& NewPosition)
{
	if (SelectedActor != NewSelectedActor)
	{
		// attempt to unselect current selection
		AActor* const OldSelection = SelectedActor.Get();
		if (OldSelection && OldSelection->GetClass()->ImplementsInterface(UP2020SelectionInterface::StaticClass()))
		{
			if (IP2020SelectionInterface::Execute_OnSelectionLost(OldSelection, NewPosition, NewSelectedActor))
			{
				SelectedActor = NULL;
			}
		}

		if (!SelectedActor.IsValid())
		{
			// attempt to select new selection
			if (NewSelectedActor && NewSelectedActor->GetClass()->ImplementsInterface(UP2020SelectionInterface::StaticClass()))
			{
				if (IP2020SelectionInterface::Execute_OnSelectionGained(NewSelectedActor))
				{
					SelectedActor = NewSelectedActor;
				}
			}
		}
	}
}

void AP2020PlayerController::OnTapPressed(const FVector2D& ScreenPosition, float DownTime)
{
	FVector WorldPosition(0.f);
	AActor* const HitActor = GetFriendlyTarget(ScreenPosition, WorldPosition);

	SetSelectedActor(HitActor, WorldPosition);

	if (HitActor && HitActor->GetClass()->ImplementsInterface(UP2020InputInterface::StaticClass()))
	{
		IP2020InputInterface::Execute_OnInputTap(HitActor);
	}
}

void AP2020PlayerController::OnHoldPressed(const FVector2D& ScreenPosition, float DownTime)
{
	FVector WorldPosition(0.0f);
	AActor* const HitActor = GetFriendlyTarget(ScreenPosition, WorldPosition);

	SetSelectedActor(HitActor, WorldPosition);

	if (HitActor && HitActor->GetClass()->ImplementsInterface(UP2020InputInterface::StaticClass()))
	{
		IP2020InputInterface::Execute_OnInputHold(HitActor);
	}
}

void AP2020PlayerController::OnHoldReleased(const FVector2D& ScreenPosition, float DownTime)
{
	AActor* const Selected = SelectedActor.Get();
	if (Selected && Selected->GetClass()->ImplementsInterface(UP2020InputInterface::StaticClass()))
	{
		IP2020InputInterface::Execute_OnInputHoldReleased(Selected, DownTime);
	}
}

void AP2020PlayerController::OnSwipeStarted(const FVector2D& AnchorPosition, float DownTime)
{
	if (GetCameraComponent() != NULL)
	{
		GetCameraComponent()->OnSwipeStarted(AnchorPosition);
	}

	FVector WorldPosition(0.0f);
	AActor* const HitActor = GetFriendlyTarget(AnchorPosition, WorldPosition);

	SetSelectedActor(HitActor, WorldPosition);

	/** Get our position in 3d space *//*
	if (SelectedActor.IsValid())
	{
		SwipeAnchor3D = SelectedActor->GetActorLocation();
	}

	PrevSwipeScreenPosition = AnchorPosition;
}

void AP2020PlayerController::OnSwipeUpdate(const FVector2D& ScreenPosition, float DownTime)
{
	AActor* const Selected = SelectedActor.Get();
	if (Selected && Selected->GetClass()->ImplementsInterface(UP2020InputInterface::StaticClass()))
	{
		ULocalPlayer* const MyPlayer = Cast<ULocalPlayer>(Player);
		const FPlane GroundPlane = FPlane(FVector(0, 0, SelectedActor->GetActorLocation().Z), FVector(0, 0, 1));

		FVector RayOrigin, RayDirection;
		FP2020Helpers::DeprojectScreenToWorld(ScreenPosition, MyPlayer, RayOrigin, RayDirection);
		const FVector ScreenPosition3D = FP2020Helpers::IntersectRayWithPlane(RayOrigin, RayDirection, GroundPlane);

		IP2020InputInterface::Execute_OnInputSwipeUpdate(Selected, ScreenPosition3D - SwipeAnchor3D);
	}
	else
	{
		if (GetCameraComponent() != NULL)
		{
			GetCameraComponent()->OnSwipeUpdate(ScreenPosition);
		}
	}

	PrevSwipeScreenPosition = ScreenPosition;
}

void AP2020PlayerController::OnSwipeReleased(const FVector2D& ScreenPosition, float DownTime)
{
	AActor* const Selected = SelectedActor.Get();
	if (Selected && Selected->GetClass()->ImplementsInterface(UP2020InputInterface::StaticClass()))
	{
		ULocalPlayer* const MyPlayer = Cast<ULocalPlayer>(this->Player);
		const FPlane GroundPlane = FPlane(FVector(0, 0, SelectedActor->GetActorLocation().Z), FVector(0, 0, 1));

		FVector RayOrigin, RayDirection;
		FP2020Helpers::DeprojectScreenToWorld(ScreenPosition, MyPlayer, RayOrigin, RayDirection);
		const FVector ScreenPosition3D = FP2020Helpers::IntersectRayWithPlane(RayOrigin, RayDirection, GroundPlane);

		IP2020InputInterface::Execute_OnInputSwipeReleased(Selected, ScreenPosition3D - SwipeAnchor3D, DownTime);
	}
	else
	{
		if (GetCameraComponent() != NULL)
		{
			GetCameraComponent()->OnSwipeReleased(ScreenPosition);
		}
	}
}*/

void AP2020PlayerController::OnSwipeTwoPointsStarted(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime)
{
	PrevSwipeMidPoint = (ScreenPosition1 + ScreenPosition2) * 0.5f;
}

void AP2020PlayerController::OnSwipeTwoPointsUpdate(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime)
{
	const FVector2D SwipeMidPoint = (ScreenPosition1 + ScreenPosition2) * 0.5f;
	const FVector MoveDir = FVector(SwipeMidPoint - PrevSwipeMidPoint, 0.0f).GetSafeNormal();
	const float SwipeSpeed = 10000.0f;

	const FRotationMatrix R(PlayerCameraManager->GetCameraRotation() + FRotator(0.0, 90.0, 0.0));
	const FVector WorldSpaceAccel = R.TransformVector(MoveDir) * SwipeSpeed;
	if (GetSpectatorPawn())
	{
		GetSpectatorPawn()->AddMovementInput(WorldSpaceAccel, 1.f);
	}

	PrevSwipeMidPoint = SwipeMidPoint;
}

void AP2020PlayerController::OnPinchStarted(const FVector2D& AnchorPosition1, const FVector2D& AnchorPosition2, float DownTime)
{
	// Pass the pinch through to the camera component.
	if (GetCameraComponent() != NULL)
	{
		GetCameraComponent()->OnPinchStarted(AnchorPosition1, AnchorPosition2, DownTime);
	}
}

void AP2020PlayerController::OnPinchUpdate(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime)
{
	// Pass the pinch through to the camera component.
	if (GetCameraComponent() != NULL)
	{
		// GetCameraComponent()->OnPinchUpdate(InputHandler, ScreenPosition1, ScreenPosition2, DownTime);
	}
}

AP2020SpectatorPawn* AP2020PlayerController::GetP2020SpectatorPawn() const
{
	return Cast<AP2020SpectatorPawn>(GetSpectatorPawn());
}

UP2020CameraComponent* AP2020PlayerController::GetCameraComponent() const
{
	UP2020CameraComponent* CameraComponent = NULL;
	if (GetP2020SpectatorPawn() != NULL)
	{
		CameraComponent = GetP2020SpectatorPawn()->GetP2020CameraComponent();
	}
	return CameraComponent;
}
