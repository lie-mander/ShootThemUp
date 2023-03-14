// Shoot Them Up Game. All Rights Reserved

#include "AI/Services/STUChangeWeaponService.h"
#include "AIController.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"

USTUChangeWeaponService::USTUChangeWeaponService() 
{
    NodeName = "Change Weapon";
}

void USTUChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
    const auto Controller = OwnerComp.GetAIOwner();

    if (Controller)
    {
        const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Controller->GetPawn());
        if (WeaponComponent)
        {
            const auto Chance = FMath::RandRange(0.0, 1.0);
            if (Chance < Probability && WeaponComponent->CanEquip())
            {
                UE_LOG(LogTemp, Display, TEXT("Lucky, chance = %f"), Chance);
                WeaponComponent->NextWeapon();
            }
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
