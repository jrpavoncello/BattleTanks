// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreMinimal.h"
#include "TankPlayerController.h"

ATankPawn* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATankPawn>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto* tank = GetControlledTank();

	if (tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController has possesed tank %s."), *(tank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController has not possesed a tank."));
	}
}
