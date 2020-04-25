// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "Math/UnrealMathUtility.h"

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