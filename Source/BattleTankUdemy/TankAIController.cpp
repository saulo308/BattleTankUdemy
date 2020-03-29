// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TankPlayerController.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay(){
    Super::BeginPlay();
    ControlledTank = GetControlledTank();
    if(!ControlledTank)
        UE_LOG(LogTemp,Error,TEXT("AIController tank not found!!"));

    PlayerTank = GetPlayerControlledTank();
    if(!PlayerTank)
        UE_LOG(LogTemp,Error,TEXT("Couldn't find the player tank!"));
}

void ATankAIController::Tick(float DeltaTime){
    Super::Tick(DeltaTime);

    if(ControlledTank && PlayerTank){
        //Move towards player

        //Aim at player
        ControlledTank->AimAt(PlayerTank->GetActorLocation());

        //Fire
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

