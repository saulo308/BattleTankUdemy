// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward Declarations
class UTankBarrel;
class UTankTurret;
class UTankTrack;

UCLASS()
class BATTLETANKUDEMY_API ATank : public APawn
{
	GENERATED_BODY()


public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable)
	void SetupTankMeshes(UTankBarrel* BarrelToSet,UTankTurret* TurretToSet,UTankTrack* LeftTrack, UTankTrack* RightTrack);
	UFUNCTION()
	virtual float TakeDamage(float DamageAmount,struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

public:
	//Static meshes to set
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	UStaticMesh* BarrelMesh;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	UStaticMesh* TurretMesh;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	UStaticMesh* TrackMesh;
private:
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int32 StartingHealth = 100.f;
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth = StartingHealth;
};
