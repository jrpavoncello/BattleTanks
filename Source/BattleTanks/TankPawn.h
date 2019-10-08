// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankPawn.generated.h"

UCLASS()
class BATTLETANKS_API ATankPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATankPawn();

private:
	UPROPERTY(EditAnywhere)
	float barrelPitchMin = -5.f;

	UPROPERTY(EditAnywhere)
	float barrelPitchMax = 25.f;

	UPROPERTY(EditAnywhere)
	float launchSpeed = 10000.f;

	UPROPERTY(EditAnywhere)
	float aimSpeed = 0.03f;

	float barrelStartPitch;

	UStaticMeshComponent* barrelComponent;
	UStaticMeshComponent* turretComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(const FVector& targetLocation);

	FVector GetWorldBarrelRotation();

};
