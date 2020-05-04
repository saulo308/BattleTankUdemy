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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void SetPhysicsConstrains();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

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
