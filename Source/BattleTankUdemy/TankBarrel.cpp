// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed){
	//Elevate Barrel the right amount according to max elevation speed
    UE_LOG(LogTemp,Warning,TEXT("Elevating at %f"),RelativeSpeed);
}