// Shoot Them Up Game. All Rights Reserved

#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"
#include "STUGameModeBase.h"
#include "Player/STUPlayerState.h"

void USTUPlayerHUDWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    OnChangedPawn(GetOwningPlayerPawn());
    if (GetOwningPlayer())
    {
        GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &USTUPlayerHUDWidget::OnChangedPawn);
    }
}

void USTUPlayerHUDWidget::OnChangedPawn(APawn* Pawn) 
{
    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(Pawn);
    if (HealthComponent)
    {
        HealthComponent->OnHealthChanged.AddUObject(this, &USTUPlayerHUDWidget::OnHealthChanged);
    }
}

float USTUPlayerHUDWidget::GetHealthPercent() const
{
    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
    if (!HealthComponent) return 0.0f;

    return HealthComponent->GetHealthPercent();
}

bool USTUPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
    const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent) return false;

    return WeaponComponent->GetWeaponUIData(UIData);
}

bool USTUPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
    const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent) return false;

    return WeaponComponent->GetWeaponAmmoData(AmmoData);
}

bool USTUPlayerHUDWidget::IsPlayerAlive() const
{
    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
    if (!HealthComponent) return false;

    return HealthComponent && !HealthComponent->IsDead();
}

bool USTUPlayerHUDWidget::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;
}

int32 USTUPlayerHUDWidget::GetCurrentRoundTime() const
{
    return GetGameMode() ? GetGameMode()->GetRoundCountDown() : 0;
}

int32 USTUPlayerHUDWidget::GetCurrentRoundNum() const
{
    return GetGameMode() ? GetGameMode()->GetCurrentRoundNum() : 0;
}

int32 USTUPlayerHUDWidget::GetRoundsNum() const
{
    return GetGameMode() ? GetGameMode()->GetGameData().RoundsNum : 0;
}

int32 USTUPlayerHUDWidget::GetKillsNum() const
{
    const auto Pawn = GetOwningPlayerPawn();
    if (!Pawn) return 0;

    const auto Controller = Pawn->GetController();
    if (!Controller) return 0;

    const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
    if (!PlayerState) return 0;

    return PlayerState->GetKillsNum();
}

void USTUPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
    if (HealthDelta < 0.0f)
    {
        OnTakeDamage();
    }
}

ASTUGameModeBase* USTUPlayerHUDWidget::GetGameMode() const
{
    if (!GetWorld()) return nullptr;
    return Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
}
