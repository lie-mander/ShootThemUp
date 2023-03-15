// Shoot Them Up Game. All Rights Reserved

#include "STUGameModeBase.h"
#include "Player/STUPlayerController.h"
#include "Player/STUBaseCharacter.h"
#include "UI/STUGameHUD.h"
#include "AIController.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameModeBase, All, All);

ASTUGameModeBase::ASTUGameModeBase() 
{
    PlayerControllerClass = ASTUPlayerController::StaticClass();
    DefaultPawnClass = ASTUBaseCharacter::StaticClass();
    HUDClass = ASTUGameHUD::StaticClass();
}

void ASTUGameModeBase::StartPlay() 
{
    Super::StartPlay();

    SpawnBots();
    StartRound();

    CurrentRound = 1;
}

UClass* ASTUGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    if (InController && InController->IsA<AAIController>())
    {
        return PawnClass;
    }
    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void ASTUGameModeBase::SpawnBots()
{
    if (!GetWorld()) return;

    for (int32 i = 0; i < GameData.PlayersNum - 1; i++)
    {
        FActorSpawnParameters SpawnInfo;
        SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        const auto STUAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
        RestartPlayer(STUAIController);
    }
}

void ASTUGameModeBase::StartRound() 
{
    RoundCountDown = GameData.RoundTime;
    GetWorldTimerManager().SetTimer(GameRountTimerHandle, this, &ASTUGameModeBase::GameTimerUpdate, 1.0f, true);
}

void ASTUGameModeBase::GameTimerUpdate() 
{
    UE_LOG(LogGameModeBase, Display, TEXT("Time: %i, Round %i/%i"), RoundCountDown, CurrentRound, GameData.RoundsNum);

    if (--RoundCountDown == 0)
    {
        GetWorldTimerManager().ClearTimer(GameRountTimerHandle);

        if (CurrentRound + 1 < GameData.RoundsNum)
        {
            CurrentRound++;
            StartRound();
        }
        else
        {
            UE_LOG(LogGameModeBase, Display, TEXT("-------- GAME OVER --------"));
        }
    }
}
