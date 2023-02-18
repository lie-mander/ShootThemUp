// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    ASTUBaseWeapon();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Shoot")
    float WeaponDamage = 10.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Shoot")
    float TraceMaxDistance = 1500.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "180.0"))
    float MaxDegressForShoot = 90.0f;

    virtual void StartFire();
    virtual void StopFire();

protected:
    virtual void BeginPlay() override;

    virtual void MakeShot();
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

    void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);
    void MakeDamage(FHitResult& HitResult);

    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    APlayerController* GetPlayerController() const;
    FVector GetMuzzleWorldLocation() const;
    FVector GetMuzzleWorldForwardVector() const;
    double GetDegreesBetweenOwnerAndTarget(FHitResult& HitResult) const;
};
