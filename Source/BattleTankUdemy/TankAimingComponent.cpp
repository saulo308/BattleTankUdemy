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
	UE_LOG(LogTemp,Warning,TEXT("Barrel:%s"), *BarrelRef->GetName());
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed){
	if(!BarrelRef) return;

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
	if(!BarrelRef) return;

	auto BarrelRotator = BarrelRef->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - BarrelRotator;

	//Elevate
	BarrelRef->Elevate(DeltaRotator.Pitch);
}

