// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"

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
		
	// TODO Fire when ready
	//ControlledTank->Fire();
}