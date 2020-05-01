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
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay(){
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet){
	BarrelRef = BarrelToSet;
	TurretRef = TurretToSet;
}

EFiringState UTankAimingComponent::GetFiringState(){
	return FiringState;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction){
	if((FPlatformTime::Seconds() - LastFireTime) <= ReloadTimeInSeconds){
		FiringState = EFiringState::Reloading;
	}else if(IsBarrelMoving()){
		FiringState = EFiringState::Aiming;
	}else{
		FiringState = EFiringState::Locked;
	}
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
		AimDirection = OutAimVelocity.GetSafeNormal();
		//UE_LOG(LogTemp,Warning,TEXT("%s AimingAt:%s"),*GetOwner()->GetName(), *AimDirection.ToString());
		//Move Barrel
		MoveBarrelTowards();
	}
	//UE_LOG(LogTemp,Warning,TEXT("%f: %s is launching at %f"),*GetOwner()->GetName(), LaunchSpeed);
}

void UTankAimingComponent::MoveBarrelTowards(){
	//Calculating delta between current barrel rotation and aim rotation
	if(!ensure(BarrelRef && TurretRef)) return;

	auto BarrelRotator = BarrelRef->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - BarrelRotator;

	//Elevate barrel
	BarrelRef->Elevate(DeltaRotator.Pitch);
	//Rotate turret
	if(FMath::Abs(DeltaRotator.Yaw) >= 180){
		TurretRef->Rotate(-DeltaRotator.Yaw);
	}else{
		TurretRef->Rotate(DeltaRotator.Yaw);
	}
}

void UTankAimingComponent::Fire(){
	if(FiringState != EFiringState::Reloading){
		//Spawning
		auto SpawnLocation = BarrelRef->GetSocketLocation(FName("BarrelMuzzle"));
		auto SpawnRotation = BarrelRef->GetSocketRotation(FName("BarelMuzzle"));
		if(!ensure(BarrelRef)) return;
		if(!ProjectileBlueprint) return;
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

bool UTankAimingComponent::IsBarrelMoving(){
	if(!ensure(BarrelRef)) return false;
	bool bIsVectorEqual = BarrelRef->GetForwardVector().Equals(AimDirection,0.01f);

	return !bIsVectorEqual;
}
