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
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

void ATank::AimAt(FVector AimLocation){
	if(!AimingComponent) return;

	AimingComponent->AimAt(AimLocation,LaunchSpeed);
}

void ATank::SetupTankMeshes(UTankBarrel* BarrelToSet,UTankTurret* TurretToSet, UTankTrack* LeftTrack, UTankTrack* RightTrack){
	//Barrel
	if(BarrelMesh)
		BarrelToSet->SetStaticMesh(BarrelMesh);

	//Turret
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

