// Shoot Them Up Game. All Rights Reserved

#include "UI/STUPlayerStatRowWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void USTUPlayerStatRowWidget::SetPlayerName(const FText& PlayerName)
{
    if (!PlayerNameTextBlock) return;
    PlayerNameTextBlock->SetText(PlayerName);
}

void USTUPlayerStatRowWidget::SetKills(const FText& Kills) 
{
    if (!KillsTextBlock) return;
    KillsTextBlock->SetText(Kills);
}

void USTUPlayerStatRowWidget::SetDeaths(const FText& Deaths) 
{
    if (!DeathsTextBlock) return;
    DeathsTextBlock->SetText(Deaths);
}

void USTUPlayerStatRowWidget::SetTeam(const FText& Team) 
{
    if (!TeamTextBlock) return;
    TeamTextBlock->SetText(Team);
}

void USTUPlayerStatRowWidget::SetPlayerIndicatorVisibility(bool Visible)
{
    if (!PlayerIndicatorImage) return;
    PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void USTUPlayerStatRowWidget::SetTeamColor(const FLinearColor& Color)
{
    if (!TeamImage) return;
    TeamImage->SetColorAndOpacity(Color);
}
