// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

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
}
