// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay(){
    Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn){
    Super::SetPawn(InPawn);

    if(InPawn){
        auto PossessedTank = Cast<ATank>(InPawn);
        if(!ensure(PossessedTank)) return;

        //Bind method to delegate(Tank's death)
        PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankAIController::OnReceiveTankDeath);
    }
}

void ATankAIController::Tick(float DeltaTime){
    Super::Tick(DeltaTime);

    auto ControlledTank = GetPawn();
    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

    if(!ensure(ControlledTank && PlayerTank && AimingComponent)) return;

    //Move towards player
    MoveToActor(PlayerTank,AcceptanceRadius);

    //Aim at player
    AimingComponent->AimAt(PlayerTank->GetActorLocation());

    //Fire
    if(AimingComponent->GetFiringState() == EFiringState::Locked)
        AimingComponent->Fire();
}

void ATankAIController::OnReceiveTankDeath(){
    UE_LOG(LogTemp,Warning,TEXT("Ai dead"));
}

