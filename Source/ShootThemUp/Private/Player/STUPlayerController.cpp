// Shoot Them Up Game. All Rights Reserved

#include "Player/STUPlayerController.h"
#include "Components/STURespawnComponent.h"
#include "STUGameModeBase.h"
#include "STUGameInstance.h"

ASTUPlayerController::ASTUPlayerController()
{
    RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("RespawnComponent");
}

void ASTUPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    if (!InputComponent) return;

    InputComponent->BindAction("PauseGame", EInputEvent::IE_Pressed, this, &ASTUPlayerController::OnPauseGame);
    InputComponent->BindAction("Mute", EInputEvent::IE_Pressed, this, &ASTUPlayerController::OnMuteSound);
}

void ASTUPlayerController::BeginPlay()
{
    if (GetWorld())
    {
        const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &ASTUPlayerController::OnMatchStateChanged);
        }
    }
}

void ASTUPlayerController::OnPauseGame()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());

    if (GameMode)
    {
        const auto CurrentMatchState = GameMode->GetCurrentMatchState();
        switch (CurrentMatchState)
        {
            case ESTUMatchState::InProgress: GameMode->SetPause(this); break;
            case ESTUMatchState::Pause: GameMode->ClearPause(); break;
            default: break;
        }
    }
}

void ASTUPlayerController::OnMatchStateChanged(ESTUMatchState State)
{
    if (State == ESTUMatchState::InProgress)
    {
        SetInputMode(FInputModeGameOnly());
        bShowMouseCursor = false;
    }
    else
    {
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
    }
}

void ASTUPlayerController::OnMuteSound()
{
    if (!GetWorld()) return;

    const auto STUGameInstance = Cast<USTUGameInstance>(GetWorld()->GetGameInstance());
    if (STUGameInstance)
    {
        STUGameInstance->ToggleVolume();
    }
}
