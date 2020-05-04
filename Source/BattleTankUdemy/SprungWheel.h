// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANKUDEMY_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceMagnitude);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void SetPhysicsConstrains();
	UFUNCTION()
	void ApplyForce();

public:
	float ForceToApply = 0.f;

protected:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* Wheel = nullptr;
	UPROPERTY(VisibleAnywhere)
	UPhysicsConstraintComponent* Spring = nullptr;
	UPROPERTY(VisibleAnywhere)
	USphereComponent* Axle = nullptr;
	UPROPERTY(VisibleAnywhere)
	UPhysicsConstraintComponent* AxleConstraint = nullptr;
};
