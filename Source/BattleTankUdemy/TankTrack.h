// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

class ASprungWheel;

/**
 * Apply movement on the tank
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKUDEMY_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

	UTankTrack();

public:
	//Throttle between -1 and +1
	UFUNCTION(BlueprintCallable)
	void SetThrottle(float Throttle);
	UFUNCTION()
	void DriveTrack(float CurrentThrottle);
	UFUNCTION()
	TArray<ASprungWheel*> GetWheels() const;

public:
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 40000000.f;
	
};
