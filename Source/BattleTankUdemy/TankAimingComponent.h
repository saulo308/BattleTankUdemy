// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//State of aiming
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKUDEMY_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

public:	
	UFUNCTION()
	void AimAt(FVector HitLocation);
	UFUNCTION(BlueprintCallable)
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
	UFUNCTION(BlueprintCallable)
	void Fire();

private:
	UFUNCTION()
	void MoveBarrelTowards(FVector AimDirection);
	
protected:
	UPROPERTY(BlueprintReadOnly)
	EFiringState FiringState = EFiringState::Locked;	
	
	//Fire properties
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000.f;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3.f;
	UPROPERTY()
	double LastFireTime = 0;
	UPROPERTY(EditDefaultsOnly,Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

private:
	//References
	UPROPERTY()
	UTankBarrel* BarrelRef = nullptr;
	UPROPERTY()
	UTankTurret* TurretRef = nullptr;
};
