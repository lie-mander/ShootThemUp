// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreTypes.h"
#include "STUHealthComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USTUHealthComponent();

    FOnDeath OnDeath;
    FOnHealthChanged OnHealthChanged;

    UFUNCTION(BlueprintCallable, Category = "Health")
    bool IsDead() const { return Health <= 0.0f; }

    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetHealthPercent() const { return Health / MaxHealth; }

    float GetHealth() const { return Health; }

    bool TryToAddHealth(float HealthAmount);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
    float MaxHealth = 100.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AutoHeal")
    bool AutoHeal = false;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AutoHeal",
        meta = (EditCondition = "AutoHeal", ClampMin = "0.0", ClampMax = "1000.0"))
    float AutoHealStartDelay = 3.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AutoHeal",
        meta = (EditCondition = "AutoHeal", ClampMin = "0.0", ClampMax = "10.0"))
    float HealUpdateRate = 0.3f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AutoHeal",
        meta = (EditCondition = "AutoHeal", ClampMin = "0.0", ClampMax = "100.0"))
    float HealModifier = 1.0f;

    virtual void BeginPlay() override;

private:
    float Health = 0.0f;

    FTimerHandle TimerAutoHeal;

    UFUNCTION()
    void OnTakeAnyDamage(
        AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

    bool IsFullHealth() const;
    void AddHealthAutoHeal();
    void SetHealth(float NewHealth);
};
