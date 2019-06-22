// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = Cast<ATank>(GetPawn());
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::Tick(float DeltaTime)
{
	if (ensure(PlayerTank))
	{
		// Move towards player
		MoveToActor(PlayerTank, AcceptanceRadius);

		// Aim towards player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		
		// TODO Fire when ready
		ControlledTank->Fire();
	}
}

