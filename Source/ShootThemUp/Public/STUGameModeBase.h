// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "STUCoreTypes.h"
#include "STUGameModeBase.generated.h"

class AAIController;

UCLASS()
class SHOOTTHEMUP_API ASTUGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    ASTUGameModeBase();

    virtual void StartPlay() override;
    virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

    float GetRoundCountDown() const { return RoundCountDown; }
    float GetCurrentRoundNum() const { return CurrentRound; }
    FGameData GetGameData() const { return GameData; }

    void Killed(AController* KillerController, AController* VictimController);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    TSubclassOf<AAIController> AIControllerClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    TSubclassOf<APawn> PawnClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    FGameData GameData;

private:
    void SpawnBots();
    void StartRound();
    void GameTimerUpdate();
    void ResetPlayers();
    void ResetOnePlayer(AController* Controller);

    void CreateTeamsInfo();
    FLinearColor DetermineColorByTeamID(int32 TeamID) const;
    void SetPlayerColor(AController* Controller);
    void LogPlayerInfo() const;

    FTimerHandle GameRountTimerHandle;

    int32 CurrentRound = 0;
    int32 RoundCountDown = 0;
};
