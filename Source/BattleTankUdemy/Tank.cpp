// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
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

float ATank::TakeDamage(float DamageAmount,struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser){
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints,0,CurrentHealth);

	UE_LOG(LogTemp,Warning,TEXT("DamageAmmount: %f - DamageToApply:%d"),DamageAmount,DamageToApply);
	CurrentHealth -= DamageToApply;
	if(CurrentHealth <= 0)
		UE_LOG(LogTemp,Warning,TEXT("Tank died"));

	return DamageToApply;
}

