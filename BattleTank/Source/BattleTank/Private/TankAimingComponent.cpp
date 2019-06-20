// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Gameframework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; // TODO should this really tick

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) return;

	FVector LaunchVelocity(0.f);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		LaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		FVector AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found"), GetWorld()->GetTimeSeconds());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%f: Not Found"), GetWorld()->GetTimeSeconds());
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

/*void UTankAimingComponent::SetTurretReference(UStaticMeshComponent* TurretToSet)
{
	Turret = TurretToSet;
}*/

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// find difference between current barrel rotation and aim direction
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotation;
	Barrel->Elevate(5); // TODO remove Magic Number
	// get xy axis rotator from above rotator
		// apply rotation to turret socket
	// get z axis rotator from above rotator
		// apply rotation to barrel socket
}