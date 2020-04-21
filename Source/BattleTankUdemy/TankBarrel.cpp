// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Math/UnrealMathUtility.h"

void UTankBarrel::Elevate(float RelativeSpeed){
	//Elevate Barrel the right amount according to max elevation speed
    
    //Clamping relative speed
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed,-1,1);

    //Calculating new Elevation on this frame and clamping it
    auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
    auto NewElevation = FMath::Clamp<float>(RawNewElevation,MinElevationDegree,MaxElevationDegree);

    //Setting new elevation
    SetRelativeRotation(FRotator(NewElevation,0,0));
}