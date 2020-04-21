// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed){
    //UE_LOG(LogTemp,Warning,TEXT("Rotate turret"));
    //Rotating the turret
    
    //Clamping Relative speed
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed,-1.f,1.f);

    //Calculating new rotation
    auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto RawNewRotation = RelativeRotation.Yaw + RotationChange;
    auto NewRotation = FMath::Clamp<float>(RawNewRotation, MinRotationDegrees,MaxRotationDegrees);

    //Setting new Rotation
    SetRelativeRotation(FRotator(0,NewRotation,0));
}