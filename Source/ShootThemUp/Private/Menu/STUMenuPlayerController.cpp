// Shoot Them Up Game. All Rights Reserved

#include "Menu/STUMenuPlayerController.h"
#include "STUGameInstance.h"

void ASTUMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();

    SetInputMode(FInputModeUIOnly());
    bShowMouseCursor = true;

    auto Instance = GetWorld()->GetGameInstance<USTUGameInstance>();
    if (Instance)
    {
        Instance->TestString = "Unreal Menu";
    }
}
