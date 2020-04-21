// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay(){
    Super::BeginPlay();

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
    FVector HitLocationResult = FVector(0);
    if(GetSightRayHitLocation(HitLocationResult)){
        PlayerTank->AimAt(HitLocationResult);
    }
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const{
    //Finding crosshair position in pixel coordinates
    //Getting viewport size
    int32 ViewportSizeX,ViewportSizeY;
    GetViewportSize(ViewportSizeX,ViewportSizeY);
    //Calculate where crosshair is in pixel coordinates
    FVector2D ScreenLocation((float)ViewportSizeX * CrosshairXLocation, (float)ViewportSizeY * CrosshairYLocation);

    //Deprojecting screen position to world and Linetracing
    FVector LookDirection;
    if(GetLookDirection(ScreenLocation,LookDirection) && GetLookVectorHitLocation(LookDirection,OutHitLocation))
        return true;

    return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation,FVector& LookDirection) const{
    FVector CameraWorldLocation; //Discarded
    return DeprojectScreenPositionToWorld(
        ScreenLocation.X,
        ScreenLocation.Y,
        CameraWorldLocation,
        LookDirection
    );
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection,FVector& HitLocation) const{
    bool bHit = false;
    FHitResult OutHit;
    FVector Start = PlayerCameraManager->GetCameraLocation();
    FVector End = Start + LookDirection * LineTraceRange;
    FCollisionQueryParams QueryParams(TEXT(""),false,PlayerTank);
    bHit = GetWorld()->LineTraceSingleByChannel(
        OutHit,
        Start,
        End,
        ECollisionChannel(ECollisionChannel::ECC_Visibility),
        QueryParams
    );
    
    HitLocation = (bHit) ? OutHit.Location : FVector(0);
    return bHit;
}