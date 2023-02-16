// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DevDamageActor.generated.h"

class USceneComponent;

UCLASS()
class SHOOTTHEMUP_API ADevDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADevDamageActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DebugSphere")
    float Radius = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DebugSphere")
    FColor SphereColor = FColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DebugSphere")
    float Damage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DebugSphere")
    bool DoFullDamage = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
