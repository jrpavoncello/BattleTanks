// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "Engine/StaticMesh.h"

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
	auto turretComponents = GetComponentsByTag(UActorComponent::StaticClass(), FName(*FString("Turret")));
	auto barrelComponents = GetComponentsByTag(UActorComponent::StaticClass(), FName(*FString("Barrel")));

	if (turretComponents.Num() > 0 && barrelComponents.Num() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found Turret and Barrel components, target %s."), *(targetLocation.ToString()));

		auto turretMesh = Cast<UStaticMeshComponent>(turretComponents[0]);
		auto barrelMesh = Cast<UStaticMeshComponent>(barrelComponents[0]);

		auto turretTransform = turretMesh->GetRelativeTransform();
		auto oldTurretRotation = turretTransform.Rotator();
		auto turretRotation = FRotator(oldTurretRotation.Pitch, targetLocation.Z, oldTurretRotation.Roll);
		FRotator turretDelta = turretRotation - oldTurretRotation;
		turretMesh->SetRelativeRotation(turretRotation);
		turretMesh->MarkRenderTransformDirty();

		UE_LOG(LogTemp, Warning, TEXT("Turret delta rotation %s."), *(turretDelta.ToString()));

		auto barrelTransform = barrelMesh->GetRelativeTransform();
		auto oldBarrelRotation = barrelTransform.Rotator();
		auto barrelRotation = FRotator(targetLocation.Y, oldBarrelRotation.Yaw, oldBarrelRotation.Roll);
		barrelMesh->SetRelativeRotation(barrelRotation);
		barrelMesh->MarkRenderTransformDirty();

		UE_LOG(LogTemp, Warning, TEXT("New relative Barrel rotation %s."), *(barrelRotation.ToString()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find Turret component."));
	}
}

