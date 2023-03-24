// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

class USTUWeaponFXComponent;
class UNiagaraSystem;
class UNiagaraComponent;
class UAudioComponent;

UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
    GENERATED_BODY()

public:
    ASTURifleWeapon();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Shoot")
    float TimeBetweenShots = 0.1f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Shoot")
    float BulletSpread = 1.5f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Shoot")
    float OnHardMoveBulletSpread = 3.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Shoot")
    float FOVZoomAngle = 50.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "VFX")
    USTUWeaponFXComponent* WeaponFXComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem* TraceFX;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FName TraceTargetName = "TraceTarget";

    virtual void StartFire() override;
    virtual void StopFire() override;
    virtual void Zoom(bool IsEnabled) override;

    virtual void SetOnHardMoveBulletSpread(bool IsHardMoving) override;

protected:
    virtual void BeginPlay() override;
    virtual void MakeShot() override;
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:
    FTimerHandle ShotTimerHandle;

    UPROPERTY()
    UNiagaraComponent* MuzzleFXComponent;

    UPROPERTY()
    UAudioComponent* FireAudioComponent;

    void InitFX();
    void SetFXActive(bool IsActive);
    void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);
    void DoShotOperators(FVector& TraceEndFX, FHitResult& HitResult);

    float DefaultFOVAngle = 90.0f;

    float CurrentBulletSpread;
};
