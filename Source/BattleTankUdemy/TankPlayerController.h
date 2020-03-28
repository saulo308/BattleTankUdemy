// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKUDEMY_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	ATank* GetControlledTank() const;
private:
	UFUNCTION()
	void AimTowardsCrosshair();
	UFUNCTION()
	bool GetSightRayHitLocation(FVector &OutHitLocation) const;

	UPROPERTY()
	ATank* PlayerTank = nullptr;
};
