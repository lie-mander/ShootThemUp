// Shoot Them Up Game. All Rights Reserved


#include "Animation/STUEquipFinishedAnimNotify.h"

void USTUEquipFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) 
{
    Super::Notify(MeshComp, Animation);
    OnNotified.Broadcast(MeshComp);
}