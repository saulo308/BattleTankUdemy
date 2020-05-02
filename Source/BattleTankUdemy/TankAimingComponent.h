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
	Locked,
	OutOfAmmo
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

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

public:	
	UFUNCTION()
	void AimAt(FVector HitLocation);
	UFUNCTION(BlueprintCallable)
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
	UFUNCTION(BlueprintCallable)
	void Fire();
	UFUNCTION()
	bool IsBarrelMoving();
	UFUNCTION()
	EFiringState GetFiringState() const;
	UFUNCTION(BlueprintCallable)
	int32 GetCurrentAmmo() const;

private:
	UFUNCTION()
	void MoveBarrelTowards();
	
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
	FVector AimDirection;
	//Ammo
	UPROPERTY(EditDefaultsOnly,Category = "Firing")
	int32 CurrentAmmo = 20;
};
