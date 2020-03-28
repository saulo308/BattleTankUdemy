// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TankPlayerController.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay(){
    ATank* ControlledTank = GetControlledTank();
    if(!ControlledTank)
        UE_LOG(LogTemp,Error,TEXT("AIController tank not found!!"));

    ATank* PlayerTank = GetPlayerControlledTank();
    if(!PlayerTank){
        UE_LOG(LogTemp,Error,TEXT("Couldn't find the player tank!"));
    }
}

ATank* ATankAIController::GetControlledTank() const{
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerControlledTank() const{
    auto PlayerController = GetWorld()->GetFirstPlayerController();
    if(!PlayerController)
        return nullptr;

    return Cast<ATankPlayerController>(PlayerController)->GetControlledTank();
}

