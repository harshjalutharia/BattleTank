// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("AI can't find player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI: Player possessed tank name: %s"), *(PlayerTank->GetName()));
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	if (GetPlayerTank())
	{
		// TODO Move towards player

		// Aim towards player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		// TODO Fire when ready
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn)
		return nullptr;
	return Cast<ATank>(PlayerPawn);
}
