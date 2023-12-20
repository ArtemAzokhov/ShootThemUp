// Shoot Them Up Game. All Rights Reserved.

#include "UI/STUPlayerStatRowWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUPlayerStatRowWidget, All, All)

void USTUPlayerStatRowWidget::SetPlayerName(const FText& Text)
{
    if (!PlayerNameTextBlock) return;
    UE_LOG(LogSTUPlayerStatRowWidget, Display, TEXT("PlayerNameTextBlock"));
    PlayerNameTextBlock->SetText(Text);
}

void USTUPlayerStatRowWidget::SetKills(const FText& Text)
{
    if (!KillsTextBlock) return;
    UE_LOG(LogSTUPlayerStatRowWidget, Display, TEXT("KillsTextBlock"));
    KillsTextBlock->SetText(Text);
}

void USTUPlayerStatRowWidget::SetDeaths(const FText& Text)
{
    if (!DeathsTextBlock) return;
    UE_LOG(LogSTUPlayerStatRowWidget, Display, TEXT("DeathsTextBlock"));
    DeathsTextBlock->SetText(Text);
}

void USTUPlayerStatRowWidget::SetTeam(const FText& Text)
{
    if (!TeamTextBlock) return;
    UE_LOG(LogSTUPlayerStatRowWidget, Display, TEXT("TeamTextBlock"));
    TeamTextBlock->SetText(Text);
}

void USTUPlayerStatRowWidget::SetPlayerIndicatorVisibility(bool Visible)
{
    if (!PlayerIndicatorImage) return;
    UE_LOG(LogSTUPlayerStatRowWidget, Display, TEXT("PlayerIndicatorImage"));
    PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void USTUPlayerStatRowWidget::SetTeamColor(const FLinearColor& Color)
{
    if (!TeamImage) return;
    TeamImage->SetColorAndOpacity(Color);
}
