// Fill out your copyright notice in the Description page of Project Settings.


#include "AutoMortar.h"

// Sets default values
AAutoMortar::AAutoMortar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAutoMortar::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}

float AAutoMortar::GetHealthPercentage(){
	return (float)CurrentHealth / (float)StartingHealth;
}

float AAutoMortar::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser){
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if(CurrentHealth <= 0){
		UE_LOG(LogTemp,Warning,TEXT("PEace out"));
		Destroy();
	}

	return DamageToApply;
}

