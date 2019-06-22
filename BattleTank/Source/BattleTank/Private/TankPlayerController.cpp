// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "GameFramework/PlayerController.h"
#include "CollisionQueryParams.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent))
		FoundAimingComponent(AimingComponent);
	else
		UE_LOG(LogTemp, Error, TEXT("Player controller can't find aiming component"));
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(AimingComponent)) return;

	FVector HitLocation; // OUT Parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
	}
}

// Get world location of linetrace through crosshair, true if it hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Get Crosshair pixel position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
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