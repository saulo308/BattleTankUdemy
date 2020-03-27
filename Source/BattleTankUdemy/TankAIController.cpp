// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay(){
    ATank* ControlledTank = GetControlledTank();

    if(!ControlledTank){
        UE_LOG(LogTemp,Warning,TEXT("AIController tank not found!!"));
    }else{
        UE_LOG(LogTemp,Warning,TEXT("The AI tank name is:%s"), *ControlledTank->GetName());
    }
}

ATank* ATankAIController::GetControlledTank() const{
    return Cast<ATank>(GetPawn());
}

