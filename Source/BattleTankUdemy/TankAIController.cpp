// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "TankPlayerController.h"

void ATankAIController::BeginPlay(){
    Super::BeginPlay();
    ControlledTank = Cast<ATank>(GetPawn());
    if(!ControlledTank)
        UE_LOG(LogTemp,Error,TEXT("AIControlled tank not found!!"));

    PlayerTank = GetPlayerControlledTank();
    if(!PlayerTank)
        UE_LOG(LogTemp,Error,TEXT("Couldn't find the player tank!"));
}

void ATankAIController::Tick(float DeltaTime){
    Super::Tick(DeltaTime);

    if(ControlledTank && PlayerTank){
        //Move towards player
        MoveToActor(PlayerTank,AcceptanceRadius);

        //Aim at player
        ControlledTank->AimAt(PlayerTank->GetActorLocation());

        //Fire
        ControlledTank->Fire();
    }
}

ATank* ATankAIController::GetPlayerControlledTank() const{
    auto PlayerController = GetWorld()->GetFirstPlayerController();
    if(!PlayerController)
        return nullptr;

    return Cast<ATankPlayerController>(PlayerController)->GetControlledTank();
}

