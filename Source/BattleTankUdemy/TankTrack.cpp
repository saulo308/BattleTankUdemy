// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "Math/UnrealMathUtility.h"

UTankTrack::UTankTrack(){
    PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay(){
    Super::BeginPlay();
    OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction){
    Super::TickComponent(DeltaTime,TickType,ThisTickFunction);

    CorrectTrackMovement(DeltaTime);
}

void UTankTrack::CorrectTrackMovement(float DeltaTime){
    //==Correcting the accelaration (i.e. prevent tank from slipping)==

    //Calculating slippage speed
    auto SplippageSpeed = FVector::DotProduct(GetRightVector(),GetComponentVelocity());

    //Calculating accelaration and then acceletarion direction(* -1 because we want it to be opossite to the movement)
    //* RightVector() because we want the direction
    //(Acceletarion = Speed / time)
    auto AccelerationCorrection = - ((SplippageSpeed / DeltaTime) * GetRightVector()); 

    //Calculating force (F = m.a)
    auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    auto AccelerationForce = (TankRoot->GetMass() * AccelerationCorrection) / 2;
    
    //Applying force
    TankRoot->AddForce(AccelerationForce);
}

void UTankTrack::SetThrottle(float Throttle){
    //UE_LOG(LogTemp,Warning,TEXT("%s throttle is %f"),*GetName(),Throttle);

    //Clamping throttle
    Throttle = FMath::Clamp<float>(Throttle,-1.f,1.f);

    //Calculation force speed and location
    auto ForceLocation = GetComponentLocation();
    auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

    //Apply force
    TankRoot->AddForceAtLocation(ForceApplied,ForceLocation);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent,AActor* OtherActor,UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit){
    UE_LOG(LogTemp,Warning,TEXT("Hit ground"));
}