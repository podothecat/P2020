// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"

#include "P2020Player.h"
#include "RoundGameMode.h"
#include "RoundGameState.h"

#define COLLISION_PANCAMERA		ECC_GameTraceChannel3

// DECLARE_LOG_CATEGORY_EXTERN(LogGame, Log, All);

#if PLATFORM_ANDROID
#define SupportsQuitButton	false
#elif PLATFORM_IOS || PLATFORM_TVOS
#define SupportsQuitButton	false
#else
#define SupportsQuitButton	FPlatformProperties::SupportsQuit()
#endif
