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

    ACharacter* Player = Cast<ACharacter>(GetOwner());
    if (!Player) return;

    AController* Controller = Player->GetController();
    if (!Controller) return;

    FVector ViewLocation;
    FRotator ViewRotation;
    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

    const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);

    const FVector TraceStart = ViewLocation;
    const FVector ShootDirection = ViewRotation.Vector();
    const FVector MuzzleLocation = SocketTransform.GetLocation();
    const FVector MuzzleDirection = SocketTransform.GetRotation().GetForwardVector();
    const FVector TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

    FHitResult HitResult;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);

    const FVector VectorToHit = (HitResult.ImpactPoint - MuzzleLocation).GetSafeNormal();
    const auto AngleBetween = FMath::Acos(FVector::DotProduct(MuzzleDirection, VectorToHit));
    const auto Degress = FMath::RadiansToDegrees(AngleBetween);

    if (HitResult.bBlockingHit && Degress <= MaxDegressForShoot)
    {
        DrawDebugLine(GetWorld(), MuzzleLocation, HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 15.0f, 24, FColor::Red, false, 4.0f);
        UE_LOG(LogBaseWeapon, Display, TEXT("Bone: %s"), *HitResult.BoneName.ToString());
    }
    else if (HitResult.bBlockingHit)
    {
        DrawDebugLine(GetWorld(), MuzzleLocation, TraceEnd, FColor::Yellow, false, 3.0f, 0, 3.0f);
        GetWorld()->LineTraceSingleByChannel(HitResult, MuzzleLocation, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
        if (HitResult.bBlockingHit)
        {
            DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 15.0f, 24, FColor::Yellow, false, 4.0f);
            UE_LOG(LogBaseWeapon, Display, TEXT("Bone: %s"), *HitResult.BoneName.ToString());
        }
    }
    else
    {
        DrawDebugLine(GetWorld(), MuzzleLocation, TraceEnd, FColor::Blue, false, 3.0f, 0, 3.0f);
    }
}
