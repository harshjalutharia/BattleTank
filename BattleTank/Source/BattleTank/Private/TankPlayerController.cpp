// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "GameFramework/PlayerController.h"
#include "CollisionQueryParams.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("No player possessed tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player possessed tank name: %s"), *(ControlledTank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) return;

	FVector HitLocation; // OUT Parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *(HitLocation.ToString()));
		// TODO tell controlled tank to aim at this point
	}
}

// Get world location of linetrace through crosshair, true if it hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Get Crosshair pixel position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	FHitResult HitResult;
	FCollisionQueryParams LineTraceParams;
	LineTraceParams.AddIgnoredActor(GetPawn());
	if (GetHitResultAtScreenPosition(ScreenLocation, ECC_Visibility, LineTraceParams, HitResult))
	{
		if (HitResult.Distance < LineTraceRange)
			HitLocation = HitResult.ImpactPoint;
		else
			HitLocation = FVector(0.f);
		return true;
	}
	else
		return false;
}