// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent))
		UE_LOG(LogTemp, Error, TEXT("AI controller can't find aiming component"));
	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ensure(Player))
		UE_LOG(LogTemp, Error, TEXT("AI controller can't find Player"));
}

void ATankAIController::Tick(float DeltaTime)
{
	if (!ensure(AimingComponent) || !ensure(Player)) return;

	// Move towards player
	MoveToActor(Player, AcceptanceRadius);

	// Aim towards player
	AimingComponent->AimAt(Player->GetActorLocation());
		
	if(AimingComponent->GetFiringState()==EFiringState::Locked)
		AimingComponent->Fire();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) return;
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	if (!GetPawn()) return;
	GetPawn()->DetachFromControllerPendingDestroy();
}
