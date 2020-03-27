// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay(){
    ATank* TankPtr = GetControlledTank();
    if(!TankPtr){
        UE_LOG(LogTemp,Warning,TEXT("PlayerController not possesing a tank"));
    }else{
        UE_LOG(LogTemp,Warning,TEXT("The tank is:%s"), *TankPtr->GetName());
    }
}

ATank* ATankPlayerController::GetControlledTank() const{
    return Cast<ATank>(GetPawn());
}