// Shoot Them Up Game. All Rights Reserved

#include "Weapon/STUBaseWeapon.h"
#include "GameFramework/Character.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All)

ASTUBaseWeapon::ASTUBaseWeapon()
{
    PrimaryActorTick.bCanEverTick = false;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

void ASTUBaseWeapon::BeginPlay()
{
    Super::BeginPlay();

    check(WeaponMesh);
}

void ASTUBaseWeapon::Fire()
{
    UE_LOG(LogBaseWeapon, Display, TEXT("Fire"));
    MakeShot();
}

void ASTUBaseWeapon::MakeShot()
{
    if (!GetWorld()) return;

    FVector TraceStart;
    FVector TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd)) return;
    
    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);
    const double Degrees = GetDegreesBetweenOwnerAndTarget(HitResult);

    if (HitResult.bBlockingHit && Degrees <= MaxDegressForShoot)
    {
        DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 15.0f, 24, FColor::Red, false, 4.0f);
        MakeDamage(HitResult);
        UE_LOG(LogBaseWeapon, Display, TEXT("Bone: %s"), *HitResult.BoneName.ToString());
    }
    else if (HitResult.bBlockingHit)
    {
        DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Yellow, false, 3.0f, 0, 3.0f);
        MakeHit(HitResult, GetMuzzleWorldLocation(), TraceEnd);
        if (HitResult.bBlockingHit)
        {
            DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 15.0f, 24, FColor::Yellow, false, 4.0f);
            MakeDamage(HitResult);
            UE_LOG(LogBaseWeapon, Display, TEXT("Bone: %s"), *HitResult.BoneName.ToString());
        }
    }
    else
    {
        DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Blue, false, 3.0f, 0, 3.0f);
    }
}

APlayerController* ASTUBaseWeapon::GetPlayerController() const
{
    ACharacter* Player = Cast<ACharacter>(GetOwner());
    if (!Player) return nullptr;

    return Player->GetController<APlayerController>();
}

bool ASTUBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const 
{
    const auto Controller = GetPlayerController();
    if (!Controller) return false;

    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
    return true;
}

FVector ASTUBaseWeapon::GetMuzzleWorldLocation() const 
{
    return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

FVector ASTUBaseWeapon::GetMuzzleWorldForwardVector() const
{
    return WeaponMesh->GetSocketTransform(MuzzleSocketName).GetRotation().GetForwardVector();
}

bool ASTUBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const 
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if(!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

    TraceStart = ViewLocation;
    const FVector ShootDirection = ViewRotation.Vector();
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
    return true;
}

void ASTUBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) 
{
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}

void ASTUBaseWeapon::MakeDamage(FHitResult& HitResult)
{
    auto Target = Cast<ACharacter>(HitResult.GetActor());
    if (!Target) return;
    Target->TakeDamage(WeaponDamage, FDamageEvent(), GetPlayerController(), this);
}

double ASTUBaseWeapon::GetDegreesBetweenOwnerAndTarget(FHitResult& HitResult) const
{
    const FVector VectorToHit = (HitResult.ImpactPoint - GetMuzzleWorldLocation()).GetSafeNormal();
    const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetMuzzleWorldForwardVector(), VectorToHit));
    return FMath::RadiansToDegrees(AngleBetween);
}
