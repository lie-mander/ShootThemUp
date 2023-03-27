// Shoot Them Up Game. All Rights Reserved

#include "STUMultiplayGameMode.h"
#include "Player/STUPlayerController.h"
#include "Player/STUPlayerCharacter.h"
#include "UI/STUGameHUD.h"

ASTUMultiplayGameMode::ASTUMultiplayGameMode() 
{
    PlayerControllerClass = ASTUPlayerController::StaticClass();
    DefaultPawnClass = ASTUPlayerCharacter::StaticClass();
    HUDClass = ASTUGameHUD::StaticClass();
}
