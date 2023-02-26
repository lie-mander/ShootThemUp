// Shoot Them Up Game. All Rights Reserved

#include "Weapon/STULauncherWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/STUProjectile.h"

void ASTULauncherWeapon::StartFire()
{
    MakeShot();
}

void ASTULauncherWeapon::MakeShot()
{
    if (!GetWorld() || IsAmmoEmpty()) return;

    FVector TraceStart;
    FVector TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd)) return;

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    if (HitResult.bBlockingHit && GetDegreesBetweenOwnerAndTarget() <= MaxDegressForShoot)
    {
        SpawnProjectileInDirection(HitResult.ImpactPoint);
    }
    else if (HitResult.bBlockingHit)
    {
        SpawnProjectileInDirection(TraceEnd);
        MakeHit(HitResult, GetMuzzleWorldLocation(), TraceEnd);
    }
    else
    {
        SpawnProjectileInDirection(TraceEnd);
    }

    DecreaseAmmo();
}

void ASTULauncherWeapon::SpawnProjectileInDirection(const FVector& EndPoint)
{
    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
    ASTUProjectile* Projectile = GetWorld()->SpawnActorDeferred<ASTUProjectile>(ProjectileClass, SpawnTransform);
    const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();
    Projectile->SetShotDirection(Direction);
    Projectile->SetOwner(GetOwner());
    Projectile->FinishSpawning(SpawnTransform);
}
