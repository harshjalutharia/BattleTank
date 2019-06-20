// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CrosshairLocation)
	float CrosshairXLocation = 0.5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CrosshairLocation)
	float CrosshairYLocation = 0.33333;
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;

private:
	ATank* GetControlledTank() const;
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	// Start the tank moving the barrel so the shot would hit where the crosshair intersects the world
	void AimTowardsCrosshair();
};
