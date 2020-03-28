// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay(){
    PlayerTank = GetControlledTank();
    if(!PlayerTank)
        UE_LOG(LogTemp,Warning,TEXT("PlayerController not possesing a tank!! PlayerTank not defined"));
}

void ATankPlayerController::Tick(float DeltaTime){
    Super::Tick(DeltaTime);

    //Aiming
    AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair(){
    if(!PlayerTank){ return; }

    //CallingRayCast
    FVector HitLocationResult = FVector().ZeroVector;
    if(GetSightRayHitLocation(HitLocationResult)){
        UE_LOG(LogTemp,Warning,TEXT("Hit!"));
    }
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const{
    return false;
}