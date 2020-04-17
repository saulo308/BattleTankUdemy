// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANKUDEMY_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void ElevateBarrel(float DegreesPerSecond);
private:
	UPROPERTY(EditAnywhere)
	float MaxDegreePerSecond = 20.f;
	UPROPERTY(EditAnywhere)
	float MaxElevationDegrees = 30.f;
	UPROPERTY(EditAnywhere)
	float MinElevationDegrees = 0.f;
};
