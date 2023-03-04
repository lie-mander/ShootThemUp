// Shoot Them Up Game. All Rights Reserved

#include "Pickups/STUBasePickup.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All)

ASTUBasePickup::ASTUBasePickup()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(50.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SetRootComponent(CollisionComponent);
}

void ASTUBasePickup::BeginPlay()
{
	Super::BeginPlay();
	
    check(CollisionComponent);
}

void ASTUBasePickup::NotifyActorBeginOverlap(AActor* OtherActor) 
{
    Super::NotifyActorBeginOverlap(OtherActor);

    const auto PlayerPawn = Cast<APawn>(OtherActor);
    if (GivePickupTo(PlayerPawn))
    {
        PickupWasTaken();
    }
}

void ASTUBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASTUBasePickup::PickupWasTaken() 
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

    if (GetRootComponent())
    {
        GetRootComponent()->SetVisibility(false, true);
    }
    FTimerHandle RespawnTimer;
    GetWorldTimerManager().SetTimer(RespawnTimer, this, &ASTUBasePickup::Respawn, RespawnTime);
}

void ASTUBasePickup::Respawn() 
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

    if (GetRootComponent())
    {
        GetRootComponent()->SetVisibility(true, true);
    }
}

bool ASTUBasePickup::GivePickupTo(APawn* PlayerPawn)
{
    return false;
}

