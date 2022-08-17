// Copyright Epic Games, Inc. All Rights Reserved.

#include "BohdanPysko_TestGameMode.h"
#include "BohdanPysko_TestHUD.h"
#include "BohdanPysko_TestCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABohdanPysko_TestGameMode::ABohdanPysko_TestGameMode()
	: Super()
{
	// Instead of using FClassFinder with hardcoded paths, set C++ classes for now,
	// then set BP Character and HUD in BP GameMode
	DefaultPawnClass = ABohdanPysko_TestCharacter::StaticClass();
	HUDClass = ABohdanPysko_TestHUD::StaticClass();
}
