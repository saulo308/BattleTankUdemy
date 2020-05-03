// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANKUDEMY_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetPawn(APawn* InPawn) override;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void FoundAimingComponent(UTankAimingComponent* AimComponentRef);
	UFUNCTION()
	void OnReceiveTankDeath();

private:
	UFUNCTION()
	void AimTowardsCrosshair();
	UFUNCTION()
	bool GetSightRayHitLocation(FVector &OutHitLocation) const;
	UFUNCTION()
	bool GetLookDirection(FVector2D ScreenLocation,FVector& LookDirection) const;
	UFUNCTION()
	bool GetLookVectorHitLocation(FVector LookDirection,FVector& HitLocation) const;

private:
	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5f;
	UPROPERTY(EditDefaultsOnly)
	float CrosshairYLocation = 0.33333f;
	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.f;
};
