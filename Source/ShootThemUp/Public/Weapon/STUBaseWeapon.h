// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUCoreTypes.h"
#include "STUBaseWeapon.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    ASTUBaseWeapon();

    FOnClipEmptySignature OnClipEmpty;

    virtual void StartFire();
    virtual void StopFire();

    void ChangeClip();
    bool CanChangeClip();

    FWeaponUIData GetUIData() const { return UIData; }
    FAmmoData GetAmmoData() const { return CurrentAmmo; }

    bool TryToAddAmmo(int32 ClipsAmount);

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Shoot")
    float WeaponDamage = 10.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Shoot")
    float TraceMaxDistance = 1500.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FAmmoData DefaultAmmo{10, 5, false};

     UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FWeaponUIData UIData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "180.0"))
    float MaxDegressForShoot = 90.0f;

    virtual void MakeShot();
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

    void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);
    void MakeDamage(FHitResult& HitResult);

    void DecreaseAmmo();
    bool IsAmmoEmpty() const;
    bool IsClipEmpty() const;
    bool IsAmmoFull() const;
    void LogAmmo() const;

    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    APlayerController* GetPlayerController() const;
    FVector GetMuzzleWorldLocation() const;
    FVector GetMuzzleWorldForwardVector() const;
    float GetDegreesBetweenOwnerAndTarget() const;
    void SetDegreesBetweenOwnerAndTarget(FHitResult& HitResult);

private:
    float DegreesBetweenOwnerAndTarget = 0.0f;
    FAmmoData CurrentAmmo;
};
