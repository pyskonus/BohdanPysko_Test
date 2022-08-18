// Bohdan Pysko. Pingle Studio test


#include "UI/MainUI.h"

#include "Components/TextBlock.h"


void UMainUI::UpdateScore(const int Score)
{
	ScoreTextBlock->SetText(FText::FromString(FString::FromInt(Score)));
}

void UMainUI::UpdateWaveIndex(const int WaveIndex)
{
	WaveIndexTextBlock->SetText(FText::FromString(FString::FromInt(WaveIndex+1)));
}
