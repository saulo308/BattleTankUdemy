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

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent,AActor* OtherActor,UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

public:
	//Throttle between -1 and +1
	UFUNCTION(BlueprintCallable)
	void SetThrottle(float Throttle);
	UFUNCTION()
	void CorrectTrackMovement(float DeltaTime);
public:
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 40000000.f;
	
};
