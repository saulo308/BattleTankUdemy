// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKUDEMY_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetPawn(APawn* InPawn) override;
private:
	UFUNCTION()
	void OnReceiveTankDeath();

private:
	UPROPERTY(EditDefaultsOnly,Category = "Setup")
	float AcceptanceRadius = 8000.f;
};
