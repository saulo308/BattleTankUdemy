// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPoint.h"
#include "SprungWheel.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USpawnPoint::USpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	Wheel = GetWorld()->SpawnActorDeferred<ASprungWheel>(
				SprungWheelBP,
				GetComponentTransform()
			);
	if(Wheel){
		Wheel->AttachToComponent(this,FAttachmentTransformRules::KeepWorldTransform);
		UGameplayStatics::FinishSpawningActor(Wheel, GetComponentTransform());
	}
}

ASprungWheel* USpawnPoint::GetWheel() const{
	return Wheel;
}


// Called every frame
void USpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

