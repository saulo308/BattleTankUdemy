// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet){
    if(!ensure(LeftTrackToSet && RightTrackToSet)){
        UE_LOG(LogTemp,Error,TEXT("Can't initialise TankMovement, Tracks are null!!!"));
        return;
    }

    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed){
    //No need to call super, we're going to replace the way AI moves with MoveActor() function
   
    //Caculating the "paralelness" of tank forward vector and the vector where the AI wants to go
    auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
    auto AIForwardIntention = MoveVelocity.GetSafeNormal();

    //We're using a dot product to calculate how "right" the forward vector is of where the AI wants to go
    //(1 = TankForward = AIForwardIntention; -1 = TankForward = -AIForwardIntention; 0 if TankForward and AIForwardIntention are perpendicular)
    auto ForwardThrow = FVector::DotProduct(TankForward,AIForwardIntention);
    
    //Calling Move forward
    IntendMoveForward(ForwardThrow);

    //We're using cross product to calculate how "right" the forward vector if of where the AI wans to rotate
    //(1 if TankForward and AIForwardRotation are perpendiculars;0 if TankForward = AIForwardIntention)
    auto RotateThrow = FVector::CrossProduct(TankForward,AIForwardIntention).Z;

    //Calling rotate
    IntendTurnRight(RotateThrow);
}

void UTankMovementComponent::IntendMoveForward(float Throw){
    if(!ensure(LeftTrack && RightTrack)) return; 
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);    
}

void UTankMovementComponent::IntendTurnRight(float Throw){
    if(!ensure(LeftTrack && RightTrack)) return;

    LeftTrack->SetThrottle(-Throw);
    RightTrack->SetThrottle(Throw);    
}
