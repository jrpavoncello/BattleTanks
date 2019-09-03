// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.h"

ATankPawn* ATankAIController::GetControlledTank() const
{
	return Cast<ATankPawn>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto* tank = GetControlledTank();

	if (tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController has possesed tank %s."), *(tank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController has not possesed a tank."));
	}

	auto* playerTank = GetPlayerTank();

	if (playerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController found player tank %s."), *(playerTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController could not find player tank."));
	}
}

ATankPawn* ATankAIController::GetPlayerTank() const
{
	auto* playerController = GetWorld()->GetFirstPlayerController();

	if (!playerController)
	{
		return nullptr;
	}

	return Cast<ATankPawn>(playerController->GetPawn());
}
