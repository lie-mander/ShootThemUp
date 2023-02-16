// Shoot Them Up Game. All Rights Reserved

#include "Components/STUHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

USTUHealthComponent::USTUHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
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
    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);
}
