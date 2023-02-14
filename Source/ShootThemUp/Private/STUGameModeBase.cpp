// Shoot Them Up Game. All Rights Reserved

#include "STUGameModeBase.h"


ASTUGameModeBase::ASTUGameModeBase() 
{
    PlayerControllerClass = ASTUPlayerController::StaticClass();
    DefaultPawnClass = ASTUBaseCharacter::StaticClass();
}
