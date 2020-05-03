// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AutoMortar.generated.h"

UCLASS()
class BATTLETANKUDEMY_API AAutoMortar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAutoMortar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	UFUNCTION(BlueprintPure)
	float GetHealthPercentage();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int32 StartingHealth = 20;
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth = StartingHealth;

};
