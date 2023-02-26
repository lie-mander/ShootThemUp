// Shoot Them Up Game. All Rights Reserved


#include "Animation/STUChangeWeaponAnimNotify.h"

void USTUChangeWeaponAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) 
{
    OnNotified.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation);
}
