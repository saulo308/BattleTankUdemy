// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "Math/UnrealMathUtility.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"

UTankTrack::UTankTrack(){
    PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::SetThrottle(float Throttle){
    float CurrentThrottle = FMath::Clamp<float>(Throttle,-1,1);
    DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle){
    //Getting the wheels of the track
    auto Wheels = GetWheels();

    //Calculating force to apply on wheels
    auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
    auto ForcePerWheel = ForceApplied / Wheels.Num();

    //Applying force on the wheel
    for(auto Wheel : Wheels){
        Wheel->AddDrivingForce(ForcePerWheel);
    }
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const{
    TArray<USceneComponent*> SpawnPoints;
    TArray<ASprungWheel*> Wheels;

    //Getting all childrens from track (All spawn points)
    GetChildrenComponents(true,SpawnPoints);

    //Getting Wheels on each spawn point
    for(auto Component : SpawnPoints){
        auto SpawnPoint = Cast<USpawnPoint>(Component);

        if(SpawnPoint && SpawnPoint->GetWheel())
            Wheels.Add(SpawnPoint->GetWheel());
    }

    return Wheels;
}