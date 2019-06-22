// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = CrosshairLocation)
	float CrosshairXLocation = 0.5;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = CrosshairLocation)
	float CrosshairYLocation = 0.33333;
	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimComRef);

private:
	
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	UTankAimingComponent* AimingComponent;

	// Start the tank moving the barrel so the shot would hit where the crosshair intersects the world
	void AimTowardsCrosshair();
};
