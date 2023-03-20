// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STULauncherWeapon.generated.h"

class ASTUProjectile;
class USoundCue;

UCLASS()
class SHOOTTHEMUP_API ASTULauncherWeapon : public ASTUBaseWeapon
{
    GENERATED_BODY()

public:
    virtual void StartFire();

    UPROPERTY(EditDefaultsOnly, Category = "Projectile")
    TSubclassOf<ASTUProjectile> ProjectileClass;

protected:
    virtual void MakeShot();

private:
    void SpawnProjectileInDirection(const FVector& EndPoint);
};
