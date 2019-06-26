// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

class ASprungWheel;

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UTankTrack();

	UFUNCTION(BlueprintCallable)
	void SetThrottle(float Throttle);

	void DriveTrack(float CurrentThrottle);

	// Max force per track per newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 60000000; // 40,000 kg tank + 1g acceleration

private:
	TArray<ASprungWheel*> GetWheels() const;
};
