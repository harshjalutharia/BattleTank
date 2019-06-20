// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto NewRotation = RelativeRotation.Yaw + (RelativeSpeed * DegreesPerSecond * GetWorld()->DeltaTimeSeconds);
	SetRelativeRotation(FRotator(0, NewRotation, 0));
}