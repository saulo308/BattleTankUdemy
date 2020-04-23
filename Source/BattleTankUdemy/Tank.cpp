// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Setting aiming component
	AimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
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

	if(PlayerInputComponent){
		PlayerInputComponent->BindAction("Fire",EInputEvent::IE_Pressed,this,&ATank::Fire);
	}
}

void ATank::AimAt(FVector AimLocation){
	AimingComponent->AimAt(AimLocation,LaunchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet){
	AimingComponent->SetBarrelReference(BarrelToSet);
	BarrelRef = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet){
	AimingComponent->SetTurretReference(TurretToSet);
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

