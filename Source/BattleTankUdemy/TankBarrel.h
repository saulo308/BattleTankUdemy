// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), HideCategories = ("Collision"))
class BATTLETANKUDEMY_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	void Elevate(float DegreesPerSecond);
private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float DegreePerSeconds = 20.f;
	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegree = 0.f;
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegree = 40.f;
	
};
