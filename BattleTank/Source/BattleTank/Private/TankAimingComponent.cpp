// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Gameframework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = GetWorld()->GetTimeSeconds();
	CurrentAmmoCount = MaxAmmoCount;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (CurrentAmmoCount == 0)
		FiringState = EFiringState::OutOfAmmo;
	else if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTime)
		FiringState = EFiringState::Reloading;
	else if (IsBarrelMoving())
		FiringState = EFiringState::Aiming;
	else
		FiringState = EFiringState::Locked;
}

EFiringState UTankAimingComponent::GetFiringState()
{
	return FiringState;
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

int32 UTankAimingComponent::GetAmmoCount()
{
	return CurrentAmmoCount;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) return;
	FVector LaunchVelocity(0);
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
		AimDirection = LaunchVelocity.GetSafeNormal();
		MoveTurretAndBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveTurretAndBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret)) return;
	// find difference between current barrel rotation and aim direction
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	//FRotator TurretRotation = Turret->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.GetNormalized().Yaw);
}

void UTankAimingComponent::Fire()
{
	if (FiringState != EFiringState::OutOfAmmo && FiringState != EFiringState::Reloading)
	{
		if (!ensure(Barrel) && !ensure(ProjectileBlueprint)) return;
		auto Projectile = GetWorld()->SpawnActor<AProjectile>
			(
				ProjectileBlueprint,
				Barrel->GetSocketLocation(FName("Projectile")),
				Barrel->GetSocketRotation(FName("Projectile"))
				);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
		CurrentAmmoCount--;
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) return false;
	if (Barrel->GetForwardVector().Equals(AimDirection, 0.01))
		return false;
	else
		return true;
}