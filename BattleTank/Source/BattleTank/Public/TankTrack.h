// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UTankTrack();
	
	void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetThrottle(float Throttle);

	void DriveTrack();

	// Max force per track per newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 60000000; // 40,000 kg tank + 1g acceleration

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void ApplySideWaysForce();

	float CurrentThrottle = 0;
};
