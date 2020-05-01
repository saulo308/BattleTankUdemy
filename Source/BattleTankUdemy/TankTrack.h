// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Apply movemento on the tank
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKUDEMY_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

	UTankTrack();

	virtual void BeginPlay() override;

public:
	//Throttle between -1 and +1
	UFUNCTION(BlueprintCallable)
	void SetThrottle(float Throttle);
	UFUNCTION()
	void ApplySidewaysForce();
	UFUNCTION()
	void DriveTrack();

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent,AActor* OtherActor,UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

public:
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 40000000.f;
private:
	UPROPERTY()
	float CurrentThrottle = 0.f;
	
};
