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
    if (!GetWorld()) return;

    FVector TraceStart;
    FVector TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd)) return;

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    if (HitResult.bBlockingHit && GetDegreesBetweenOwnerAndTarget() <= MaxDegressForShoot)
    {
        SpawnProjectileInDirection(HitResult.ImpactPoint);
        MakeDamage(HitResult);
    }
    else if (HitResult.bBlockingHit)
    {
        DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Yellow, false, 3.0f, 0, 3.0f);
        SpawnProjectileInDirection(TraceEnd);
        MakeHit(HitResult, GetMuzzleWorldLocation(), TraceEnd);
        if (HitResult.bBlockingHit)
        {
            DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 15.0f, 24, FColor::Yellow, false, 4.0f);
            MakeDamage(HitResult);
        }
    }
    else
    {
        SpawnProjectileInDirection(TraceEnd);
        DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Blue, false, 3.0f, 0, 3.0f);
    }
}

void ASTULauncherWeapon::SpawnProjectileInDirection(const FVector& EndPoint) {
    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
    ASTUProjectile* Projectile = GetWorld()->SpawnActorDeferred<ASTUProjectile>(ProjectileClass, SpawnTransform);
    const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();
    Projectile->SetShotDirection(Direction);
    Projectile->FinishSpawning(SpawnTransform);
}
