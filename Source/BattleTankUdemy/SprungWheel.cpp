// Fill out your copyright notice in the Description page of Project Settings.


#include "SprungWheel.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	//Setting components
	Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring"));
	SetRootComponent(Spring);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(Spring);

	AxleConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axle Constraint"));
	AxleConstraint->SetupAttachment(Axle);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axle);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);

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
		Axle,
		NAME_None
	);

	AxleConstraint->SetConstrainedComponents
	(
		Axle,
		NAME_None,
		Wheel,
		NAME_None
	);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(GetWorld()->TickGroup == TG_PostPhysics){
		ForceToApply = 0.f;
	}
}

void ASprungWheel::AddDrivingForce(float ForceMagnitude){
	ForceToApply += ForceMagnitude;
}

void ASprungWheel::ApplyForce(){
	//Apply force on wheel
	Wheel->AddForce(Axle->GetForwardVector() * ForceToApply);
}

void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit){
	ApplyForce();
}

