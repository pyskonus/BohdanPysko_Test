// Bohdan Pysko. Pingle Studio test

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUI.generated.h"

class UTextBlock;


UCLASS()
class BOHDANPYSKO_TEST_API UMainUI : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateScore(const int Score);

	void UpdateWaveIndex(const int WaveIndex);

protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* WaveIndexTextBlock;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* ScoreTextBlock;
};
