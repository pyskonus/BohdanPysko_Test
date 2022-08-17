// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BohdanPysko_TestHUD.generated.h"

UCLASS()
class ABohdanPysko_TestHUD : public AHUD
{
	GENERATED_BODY()

public:
	ABohdanPysko_TestHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	UPROPERTY(EditDefaultsOnly, Category = "Custom Properties")
	class UTexture2D* CrosshairTex;

};

