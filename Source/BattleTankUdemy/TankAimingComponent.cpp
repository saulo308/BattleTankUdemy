// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet){
	BarrelRef = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed){
	if(!BarrelRef){
		UE_LOG(LogTemp,Error,TEXT("Attempt to aim without barrel ref! - TankAimingComponent.cpp"));
		return;
	}

	//Calculating launching direction
	FVector OutLaunchVelocity(0);
	FVector StartLocation = BarrelRef->GetSocketLocation(FName("ProjectileSocket"));
	//Getting direction
	bool bSuggestedDirection = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if(bSuggestedDirection){
		//Normalize
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();

		//MoveBarrel
		MoveBarrel(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection){
	//Difference between aim rotation and barrel rotation
	auto BarrelRotator = BarrelRef->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotation = AimRotator - BarrelRotator;

	//MoveBarrel
	//BarrelRef->ElevateBarrel(5.f);
}

