// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay(){
    Super::BeginPlay();

    //Getting AimingComponent from Pawn(Tank)
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if(!ensure(AimingComponent)) return;

    //Setting widget(Crosshair)
    FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::SetPawn(APawn* InPawn){
    Super::SetPawn(InPawn);

    if(InPawn){
        auto PossessedTank = Cast<ATank>(InPawn);
        if(!ensure(PossessedTank)) return;

        PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankPlayerController::OnReceiveTankDeath);
    }
}

void ATankPlayerController::Tick(float DeltaTime){
    Super::Tick(DeltaTime);

    //Aiming
    AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair(){
    if(!GetPawn()) return;

    //Getting AimingComponent from Pawn(Tank)
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if(!ensure(AimingComponent)) return;

    //CallingRayCast and retrieving HitLocationResult
    FVector HitLocationResult = FVector(0);
    if(GetSightRayHitLocation(HitLocationResult)){
        AimingComponent->AimAt(HitLocationResult);
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
    FCollisionQueryParams QueryParams(TEXT(""),false,GetPawn());
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

void ATankPlayerController::OnReceiveTankDeath(){
    StartSpectatingOnly();
}