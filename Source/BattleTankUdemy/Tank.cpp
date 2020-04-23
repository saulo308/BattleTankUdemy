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
	if(!BarrelRef){
		UE_LOG(LogTemp,Error,TEXT("Attempt to fire but barrel reference is undefined!!"));
		return;
	}

	UE_LOG(LogTemp,Warning,TEXT("Firing"));

	auto SpawnLocation = BarrelRef->GetSocketLocation(FName("BarrelMuzzle"));
	auto SpawnRotation = BarrelRef->GetSocketRotation(FName("BarelMuzzle"));
	GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint,
		SpawnLocation,
		SpawnRotation
	);
}

