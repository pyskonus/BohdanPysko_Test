// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BohdanPysko_TestHUD.generated.h"

class UMainUI;


UCLASS()
class ABohdanPysko_TestHUD : public AHUD
{
	GENERATED_BODY()

public:
	ABohdanPysko_TestHUD();

	/// Primary draw call for the HUD
	virtual void DrawHUD() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMainUI> MainUI_BPClass;

	virtual void BeginPlay() override;

private:
	/// Crosshair asset pointer
	UPROPERTY(EditDefaultsOnly, Category = "Custom Properties")
	class UTexture2D* CrosshairTex;

	UPROPERTY()
	UMainUI* MainUIWidget;

public:
	void UpdateScore(const int Score);

	void UpdateWaveIndex(const int WaveIndex);

};

