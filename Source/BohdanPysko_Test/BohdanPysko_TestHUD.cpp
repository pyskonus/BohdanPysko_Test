// Copyright Epic Games, Inc. All Rights Reserved.

#include "BohdanPysko_TestHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "UI/MainUI.h"

ABohdanPysko_TestHUD::ABohdanPysko_TestHUD()
{
}


void ABohdanPysko_TestHUD::DrawHUD()
{
	Super::DrawHUD();

	// Draw very simple crosshair

	// find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition( (Center.X),
										   (Center.Y + 20.0f));

	// draw the crosshair
	FCanvasTileItem TileItem( CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem( TileItem );
}

void ABohdanPysko_TestHUD::BeginPlay()
{
	Super::BeginPlay();

	if (ensure (MainUI_BPClass))
	{
		MainUIWidget = Cast<UMainUI>(CreateWidget<UUserWidget>(GetWorld(), MainUI_BPClass));
		if (ensure(MainUIWidget))
		{
			MainUIWidget->AddToViewport();
		}
	}
}

void ABohdanPysko_TestHUD::UpdateScore(const int Score)
{
	MainUIWidget->UpdateScore(Score);
}

void ABohdanPysko_TestHUD::UpdateWaveIndex(const int Score)
{
	MainUIWidget->UpdateWaveIndex(Score);
}