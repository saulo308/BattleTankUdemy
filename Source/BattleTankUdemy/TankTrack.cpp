// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "Math/UnrealMathUtility.h"

UTankTrack::UTankTrack(){
    PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay(){
    Super::BeginPlay();
    OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent,AActor* OtherActor,UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit){
    //DriveTrack (Apply forces)
    DriveTrack();
    //Apply sideways force
    ApplySidewaysForce();
    //Reset Throttle
    CurrentThrottle = 0;
}

void UTankTrack::ApplySidewaysForce(){
    //==Correcting the accelaration (i.e. prevent tank from slipping)==

    //Calculating slippage speed
    auto SplippageSpeed = FVector::DotProduct(GetRightVector(),GetComponentVelocity());

    //Calculating accelaration and then acceletarion direction(* -1 because we want it to be opossite to the movement)
    //* RightVector() because we want the direction
    //(Acceletarion = Speed / time)
    auto DeltaTime = GetWorld()->GetDeltaSeconds();
    auto AccelerationCorrection = - ((SplippageSpeed / DeltaTime) * GetRightVector()); 

    //Calculating force (F = m.a)
    auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    auto AccelerationForce = (TankRoot->GetMass() * AccelerationCorrection) / 2;
    
    //Applying force
    TankRoot->AddForce(AccelerationForce);
}

void UTankTrack::SetThrottle(float Throttle){
    CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle,-1,1);
}

void UTankTrack::DriveTrack(){
    //Calculation force speed and location
    auto ForceLocation = GetComponentLocation();
    auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

    //Apply force
    TankRoot->AddForceAtLocation(ForceApplied,ForceLocation);
}