// Shoot Them Up Game. All Rights Reserved

#include "Weapon/STURifleWeapon.h"
#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

ASTURifleWeapon::ASTURifleWeapon()
{
    WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");
}

void ASTURifleWeapon::BeginPlay()
{
    Super::BeginPlay();

    check(WeaponFXComponent);
}

void ASTURifleWeapon::StartFire()
{
    InitFX();
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASTURifleWeapon::MakeShot, TimeBetweenShots, true);
    MakeShot();
}

void ASTURifleWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
    SetFXActive(false);
}

void ASTURifleWeapon::MakeShot()
{
    Super::MakeShot();

    if (IsAmmoEmpty())
    {
        StopFire();
        return;
    }

    FVector TraceStart;
    FVector TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd))
    {
        StopFire();
        return;
    }

    FHitResult HitResultFromView;
    MakeHit(HitResultFromView, TraceStart, TraceEnd);

    FVector TraceEndFX = TraceEnd;

    if (HitResultFromView.bBlockingHit && GetDegreesBetweenOwnerAndTarget() <= MaxDegressForShoot)
    {
        FHitResult HitResultFromMuzzle;
        MakeHit(HitResultFromMuzzle, GetMuzzleWorldLocation(), HitResultFromView.ImpactPoint);

        if (HitResultFromMuzzle.bBlockingHit)
        {
            DoShotOperators(TraceEndFX, HitResultFromMuzzle);
        }
        else
        {
            DoShotOperators(TraceEndFX, HitResultFromView);
        }
    }
    else if (HitResultFromView.bBlockingHit)
    {
        MakeHit(HitResultFromView, GetMuzzleWorldLocation(), TraceEnd);

        if (HitResultFromView.bBlockingHit)
        {
            MakeDamage(HitResultFromView);
            WeaponFXComponent->PlayImpactFX(HitResultFromView);
        }
    }
    else
    {
        FHitResult HitResultFromMuzzle;
        MakeHit(HitResultFromMuzzle, GetMuzzleWorldLocation(), TraceEnd);

        if (HitResultFromMuzzle.bBlockingHit)
        {
            DoShotOperators(TraceEndFX, HitResultFromMuzzle);
        }
    }

    SpawnTraceFX(GetMuzzleWorldLocation(), TraceEndFX);
    DecreaseAmmo();
}

void ASTURifleWeapon::DoShotOperators(FVector& TraceEndFX, FHitResult& HitResult)
{
    TraceEndFX = HitResult.ImpactPoint;
    MakeDamage(HitResult);
    WeaponFXComponent->PlayImpactFX(HitResult);
}

bool ASTURifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

    TraceStart = ViewLocation;
    const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
    const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
    return true;
}

void ASTURifleWeapon::InitFX()
{
    if (!MuzzleFXComponent)
    {
        MuzzleFXComponent = SpawnMuzzleFX();
    }

    FireAudioComponent = UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);

    SetFXActive(true);
}

void ASTURifleWeapon::SetFXActive(bool IsActive)
{
    if (MuzzleFXComponent)
    {
        MuzzleFXComponent->SetPaused(!IsActive);
        MuzzleFXComponent->SetVisibility(IsActive, true);
    }

    if (FireAudioComponent)
    {
        IsActive ? FireAudioComponent->Play() : FireAudioComponent->Stop();
    }
}

void ASTURifleWeapon::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd)
{
    const auto TraceFXCmponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart);
    if (TraceFXCmponent)
    {
        TraceFXCmponent->SetVariableVec3(TraceTargetName, TraceEnd);
    }
}
