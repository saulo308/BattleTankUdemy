// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTank;

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
	UFUNCTION()
	bool GetLookDirection(FVector2D ScreenLocation,FVector& LookDirection) const;
	UFUNCTION()
	bool GetLookVectorHitLocation(FVector LookDirection,FVector& HitLocation) const;

	UPROPERTY()
	ATank* PlayerTank = nullptr;
	UPROPERTY(Editanywhere)
	float CrosshairXLocation = 0.5f;
	UPROPERTY(Editanywhere)
	float CrosshairYLocation = 0.33333f;
	UPROPERTY(Editanywhere)
	float LineTraceRange = 1000000.f;
};
