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

	FVector hitLocation(0);
	FVector cameraWorldRotation(0);
	if (GetSightRayHitLocation(hitLocation, cameraWorldRotation))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Crosshair hit detected at %s"), *(hitLocation.ToString()));

		pawn->AimAt(hitLocation);

		barrelRotationAtLastHit = pawn->GetWorldBarrelRotation();
	}
	else if(barrelRotationAtLastHit != FVector(0))
	{
		UE_LOG(LogTemp, Warning, TEXT("WorldDirection %s, BarrelRotation %s"), *(cameraWorldRotation.ToString()), *(barrelRotationAtLastHit.ToString()));

		FVector dummyWorldVector = FVector(cameraWorldRotation.X, cameraWorldRotation.Y, barrelRotationAtLastHit.Z) * 10000.f + pawn->GetActorTransform().GetLocation();

		UE_LOG(LogTemp, Warning, TEXT("Dummy AimAt vector %s"), *(dummyWorldVector.ToString()));

		pawn->AimAt(dummyWorldVector);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& out_hitLocation, FVector& out_cameraWorldRotation) const
{
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);

	FVector2D screenLocation = FVector2D(viewportSizeX * this->CrosshairXLocation, viewportSizeY * this->CrosshairYLocation);

	FVector worldLocation(0);
	if (DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, worldLocation, out_cameraWorldRotation))
	{
		FCollisionQueryParams queryParams = FCollisionQueryParams::DefaultQueryParam;
		FCollisionResponseParams responseParams = FCollisionResponseParams::DefaultResponseParam;

		float collisionDistance = 2000000.f;

		FVector lineStart = worldLocation;
		FVector lineEnd = lineStart + (out_cameraWorldRotation * collisionDistance);

		auto* world = GetWorld();

		//DrawDebugLine(world, lineStart, lineEnd, FColor(255, 0, 0), false, 0.f, 0.f, 10.f);

		FHitResult hitResult;
		if (world->LineTraceSingleByChannel(hitResult, worldLocation, lineEnd, ECollisionChannel::ECC_Visibility, queryParams, responseParams))
		{
			out_hitLocation = hitResult.Location;

			return true;
		}
	}
	else
	{
		out_cameraWorldRotation = FVector(0);
	}

	UE_LOG(LogTemp, Warning, TEXT("No crosshair hit detected."));

	out_hitLocation = FVector(0);

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
