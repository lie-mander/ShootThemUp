// Shoot Them Up Game. All Rights Reserved

#include "Dev/DevDamageActor.h"
#include <Kismet/GameplayStatics.h>

ADevDamageActor::ADevDamageActor()
{
    PrimaryActorTick.bCanEverTick = true;

    SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    SceneComponent->SetupAttachment(GetRootComponent());
}

void ADevDamageActor::BeginPlay()
{
    Super::BeginPlay();
}

void ADevDamageActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, SphereColor);
    UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, nullptr, {}, this, nullptr, DoFullDamage);
}
