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

void ASTUBaseWeapon::StartFire()
{

}

void ASTUBaseWeapon::StopFire()
{

}

void ASTUBaseWeapon::MakeShot()
{

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

float ASTUBaseWeapon::GetDegreesBetweenOwnerAndTarget() const
{
    return DegreesBetweenOwnerAndTarget;
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
    SetDegreesBetweenOwnerAndTarget(HitResult);
}

void ASTUBaseWeapon::MakeDamage(FHitResult& HitResult)
{
    auto Target = Cast<ACharacter>(HitResult.GetActor());
    if (!Target) return;
    Target->TakeDamage(WeaponDamage, FDamageEvent(), GetPlayerController(), this);
}

void ASTUBaseWeapon::SetDegreesBetweenOwnerAndTarget(FHitResult& HitResult)
{
    const FVector VectorToHit = (HitResult.ImpactPoint - GetMuzzleWorldLocation()).GetSafeNormal();
    const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetMuzzleWorldForwardVector(), VectorToHit));
    DegreesBetweenOwnerAndTarget = FMath::RadiansToDegrees(AngleBetween);
}
