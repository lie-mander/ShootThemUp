// Shoot Them Up Game. All Rights Reserved

#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"

float USTUPlayerHUDWidget::GetHealthPercent() const
{
    const auto Character = GetOwningPlayerPawn();
    if (!Character) return 0.0f;

    const auto Component = Character->GetComponentByClass(USTUHealthComponent::StaticClass());
    const auto HealthComponent = Cast<USTUHealthComponent>(Component);
    if (!HealthComponent) return 0.0f;

    return HealthComponent->GetHealthPercent();
}

bool USTUPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
    const auto Character = GetOwningPlayerPawn();
    if (!Character) return false;

    const auto Component = Character->GetComponentByClass(USTUWeaponComponent::StaticClass());
    const auto WeaponComponent = Cast<USTUWeaponComponent>(Component);
    if (!WeaponComponent) return false;

    return WeaponComponent->GetWeaponUIData(UIData);
}
