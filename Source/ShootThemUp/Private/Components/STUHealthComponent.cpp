// Shoot Them Up Game. All Rights Reserved

#include "Components/STUHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

USTUHealthComponent::USTUHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool USTUHealthComponent::TryToAddHealth(float HealthAmount)
{
    if (IsDead() || IsFullHealth() || HealthAmount < 0) return false;

    SetHealth(Health + HealthAmount);
    return true;
}

void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
    check(MaxHealth > 0);

	SetHealth(MaxHealth);

	AActor* Component = GetOwner();
    if (Component)
    {
        Component->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
    }
}

void USTUHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if (Damage <= 0.0f || IsDead() || !GetWorld()) return;
    SetHealth(Health - Damage);

    if (IsDead())
    {
        GetOwner()->GetWorldTimerManager().ClearTimer(TimerAutoHeal);
        OnDeath.Broadcast();
    }
    else if (AutoHeal)
    {
        GetOwner()->GetWorldTimerManager().SetTimer(
        TimerAutoHeal, this, &USTUHealthComponent::AddHealthAutoHeal, HealUpdateRate, AutoHeal, AutoHealStartDelay);
    }

    PlayCameraShake();
}

bool USTUHealthComponent::IsFullHealth() const
{
    return FMath::IsNearlyEqual(Health, MaxHealth);
}

void USTUHealthComponent::AddHealthAutoHeal()
{
    if (Health >= MaxHealth)
    {
        GetOwner()->GetWorldTimerManager().ClearTimer(TimerAutoHeal);
        return;
    }
    SetHealth(Health + HealModifier);
}

void USTUHealthComponent::SetHealth(float NewHealth) 
{
    const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    const auto HealthDelta = NextHealth - Health;
    Health = NextHealth;

    OnHealthChanged.Broadcast(Health, HealthDelta);
}

void USTUHealthComponent::PlayCameraShake()
{
    if (IsDead()) return;

    const auto Player = Cast<APawn>(GetOwner());
    if (!Player) return;

    const auto Controller = Player->GetController<APlayerController>();
    if (!Controller || !Controller->PlayerCameraManager) return;

    Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}
