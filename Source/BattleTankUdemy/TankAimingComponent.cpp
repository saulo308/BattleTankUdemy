// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet){
	BarrelRef = BarrelToSet;
	TurretRef = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation){
	if(!ensure(BarrelRef)) return;

	FVector OutAimVelocity;
	FVector StartLocation = BarrelRef->GetSocketLocation(FName("BarrelMuzzle"));
	bool bHasProjectileVelocity = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutAimVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if(bHasProjectileVelocity){
		auto AimDirection = OutAimVelocity.GetSafeNormal();
		//UE_LOG(LogTemp,Warning,TEXT("%s AimingAt:%s"),*GetOwner()->GetName(), *AimDirection.ToString());
		//Move Barrel
		MoveBarrelTowards(AimDirection);
	}
	//UE_LOG(LogTemp,Warning,TEXT("%f: %s is launching at %f"),*GetOwner()->GetName(), LaunchSpeed);
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection){
	//Calculating delta between current barrel rotation and aim rotation
	if(!ensure(BarrelRef && TurretRef)) return;

	auto BarrelRotator = BarrelRef->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - BarrelRotator;

	//Elevate barrel
	BarrelRef->Elevate(DeltaRotator.Pitch);
	//Rotate turret
	TurretRef->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire(){
	if(!ensure(BarrelRef && ProjectileBlueprint)) return;

	bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) >= ReloadTimeInSeconds;

	if(bIsReloaded){
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
