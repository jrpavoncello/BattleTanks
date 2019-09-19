// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "Engine/StaticMesh.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATankPawn::ATankPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();

	auto turretComponents = GetComponentsByTag(UActorComponent::StaticClass(), FName(*FString("Turret")));
	auto barrelComponents = GetComponentsByTag(UActorComponent::StaticClass(), FName(*FString("Barrel")));

	if (turretComponents.Num() > 0 && barrelComponents.Num() > 0)
	{
		turretComponent = Cast<UStaticMeshComponent>(turretComponents[0]);
		barrelComponent = Cast<UStaticMeshComponent>(barrelComponents[0]);

		if (turretComponent == nullptr || barrelComponent == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Turret and Barrel components were not of type UStaticMeshComponent."));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Found Turret and Barrel components."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find Turret and Barrel components."));
	}
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATankPawn::AimAt(const FVector& targetLocation)
{
	if (turretComponent != nullptr && barrelComponent != nullptr)
	{
		auto turretWorldTransform = turretComponent->GetComponentTransform();
		auto worldTargetVec = targetLocation - turretWorldTransform.GetLocation();

		// Maps the world vector to the target into a local delta from the turrets current rotation
		auto turretDelta = turretWorldTransform.Rotator().UnrotateVector(worldTargetVec).Rotation();

		auto barrelPitchToTarget = turretDelta.Pitch;

		turretDelta.Pitch = 0.f;
		turretDelta.Roll = 0.f;

		turretComponent->AddRelativeRotation(turretDelta);

		barrelPitchToTarget = FMath::Clamp<float>(barrelPitchToTarget, barrelPitchMin, barrelPitchMax);

		auto barrelLocalRot = FRotator(barrelPitchToTarget, 0.f, 0.f);

		barrelComponent->SetRelativeRotation(barrelLocalRot);

		UE_LOG(LogTemp, Warning, TEXT("Relative barrel rotation %s."), *(barrelLocalRot.ToString()));
	}
}

