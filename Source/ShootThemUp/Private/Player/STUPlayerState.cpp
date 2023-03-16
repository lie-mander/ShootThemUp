// Shoot Them Up Game. All Rights Reserved

#include "Player/STUPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogPlayerState, All, All);

void ASTUPlayerState::SubKills(int32 Amount) 
{
    KillsNum = KillsNum - Amount > 0 ? KillsNum - Amount : 0;
}

void ASTUPlayerState::LogInfo() const
{
    UE_LOG(LogPlayerState, Display, TEXT("TeamID: %i, Kills = %i, Deaths = %i"), TeamID, KillsNum, DeathsNum);
}
