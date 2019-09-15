// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

ATankPawn* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATankPawn>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	auto pawn = GetControlledTank();

	if (!pawn)
	{
		return;
	}

	FVector hitLocation;
	if (GetSightRayHitLocation(hitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Crosshair hit detected at %s"), *(hitLocation.ToString()));

		pawn->AimAt(hitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& out_hitLocation) const
{
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);

	FVector2D screenLocation = FVector2D(viewportSizeX * this->CrosshairXLocation, viewportSizeY * this->CrosshairYLocation);

	FVector worldLocation;
	FVector worldDirection;
	if (DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, worldLocation, worldDirection))
	{
		FCollisionQueryParams queryParams = FCollisionQueryParams::DefaultQueryParam;
		FCollisionResponseParams responseParams = FCollisionResponseParams::DefaultResponseParam;

		float collisionDistance = 2000000.f;

		FVector lineStart = worldLocation;
		FVector lineEnd = lineStart + (worldDirection * collisionDistance);

		auto* world = GetWorld();

		//DrawDebugLine(world, lineStart, lineEnd, FColor(255, 0, 0), false, 0.f, 0.f, 10.f);

		FHitResult hitResult;
		if (world->LineTraceSingleByChannel(hitResult, worldLocation, lineEnd, ECollisionChannel::ECC_Visibility, queryParams, responseParams))
		{
			out_hitLocation = hitResult.Location;

			return true;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("No crosshair hit detected."));

	out_hitLocation = FVector(0, 0, 0);

	return false;
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

void ATankPlayerController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	AimTowardsCrosshair();
}
