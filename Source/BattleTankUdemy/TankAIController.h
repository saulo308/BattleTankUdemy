// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTank;

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
	
private:
	UFUNCTION()
	ATank* GetControlledTank() const;
	UFUNCTION()
	ATank* GetPlayerControlledTank() const;

	UPROPERTY()
	ATank* PlayerTank = nullptr;
	UPROPERTY()
	ATank* ControlledTank = nullptr;
};
