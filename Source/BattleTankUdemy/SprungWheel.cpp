// Fill out your copyright notice in the Description page of Project Settings.


#include "SprungWheel.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setting components
	Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring"));
	SetRootComponent(Spring);

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Spring);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	SetPhysicsConstrains();
}

void ASprungWheel::SetPhysicsConstrains(){
	if(!GetAttachParentActor()) return;

	UPrimitiveComponent* TankBody = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if(!TankBody) return;

	Spring->SetConstrainedComponents
	(
		TankBody,
		NAME_None,
		Wheel,
		NAME_None
	);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

