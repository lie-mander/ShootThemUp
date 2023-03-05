// Shoot Them Up Game. All Rights Reserved

#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"

USTUWeaponFXComponent::USTUWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponFXComponent::PlayImpactFX(const FHitResult& Hit) 
{
    auto Effect = DefaultEffect;

    if (Hit.PhysMaterial.IsValid())
    {
        const auto PhysMaterial = Hit.PhysMaterial.Get();
        if (EffectsMap.Contains(PhysMaterial))
        {
            Effect = EffectsMap[PhysMaterial];
        }
    }
    UE_LOG(LogTemp, Display, TEXT("%s"), *Hit.GetActor()->GetName());
    UE_LOG(LogTemp, Display, TEXT("%s"), *Hit.BoneName.ToString());
    
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}
