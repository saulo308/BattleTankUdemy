// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet){
    if(!LeftTrackToSet || !RightTrackToSet){
        UE_LOG(LogTemp,Error,TEXT("Can't initialise TankMovement, Tracks are null!!!"));
        return;
    }

    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw){
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);    
}
