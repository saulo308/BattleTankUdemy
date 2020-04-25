// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward Declarations
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;

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
	
	UPROPERTY()
	UTankAimingComponent* AimingComponent = nullptr;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void AimAt(FVector AimLocation);
	UFUNCTION(BlueprintCallable)
	void Fire();
	UFUNCTION(BlueprintCallable)
	void SetTankReferences(UTankBarrel* BarrelToSet,UTankTurret* TurretToSet);

public:
	//Static meshes to set
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	UStaticMesh* BarrelMesh;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	UStaticMesh* TurretMesh;

private:
	//Fire properties
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000.f;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3.f;
	UPROPERTY()
	double LastFireTime = 0;

	UPROPERTY(EditDefaultsOnly,Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	//Barrel
	UPROPERTY()
	UTankBarrel* BarrelRef = nullptr;
};
