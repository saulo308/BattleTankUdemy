// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankTurret.h"
#include "TankTrack.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Setting aiming component
	AimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	MovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::AimAt(FVector AimLocation){
	AimingComponent->AimAt(AimLocation,LaunchSpeed);
}

void ATank::SetTankReferences(UTankBarrel* BarrelToSet,UTankTurret* TurretToSet, UTankTrack* LeftTrack, UTankTrack* RightTrack){
	//Barrel
	AimingComponent->SetBarrelReference(BarrelToSet);
	BarrelRef = BarrelToSet;
	if(BarrelMesh)
		BarrelRef->SetStaticMesh(BarrelMesh);

	//Turret
	AimingComponent->SetTurretReference(TurretToSet);
	if(TurretMesh)
		TurretToSet->SetStaticMesh(TurretMesh);

	//Tracks
	if(TrackMesh){
		LeftTrack->SetStaticMesh(TrackMesh);
		RightTrack->SetStaticMesh(TrackMesh);
	}
}

void ATank::Fire(){
	bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) >= ReloadTimeInSeconds;

	if(BarrelRef && bIsReloaded){
		//Spawning
		auto SpawnLocation = BarrelRef->GetSocketLocation(FName("BarrelMuzzle"));
		auto SpawnRotation = BarrelRef->GetSocketRotation(FName("BarelMuzzle"));
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			SpawnLocation,
			SpawnRotation
		);

		//Launching
		Projectile->LaunchProjectile(LaunchSpeed);

		//Reset fire time
		LastFireTime = FPlatformTime::Seconds();
	}
}

