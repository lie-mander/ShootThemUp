// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "STUPlayerState.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    void SetTeamID(int32 ID) { TeamID = ID; }
    int32 GetTeamID() const { return TeamID; }

    void SetTeamColor(const FLinearColor& Color) { TeamColor = Color; }
    FLinearColor GetTeamColor() const { return TeamColor; }

    void AddKill() { KillsNum++; }
    void SubKills(int32 Amount);
    int32 GetKillsNum() const { return KillsNum; }

    void AddDeath() { DeathsNum++; }
    int32 GetDeathsNum() const { return DeathsNum; }

    void LogInfo() const;

private:
    int32 TeamID;
    FLinearColor TeamColor;

    int32 KillsNum;
    int32 DeathsNum;
};
