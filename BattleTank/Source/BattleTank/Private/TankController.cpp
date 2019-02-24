// Fill out your copyright notice in the Description page of Project Settings.

#include "TankController.h"

void ATankController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	//get world location if line trace crosshair
		//if it hits landscape
		//tell take to aim at this oint
}

void ATankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
	//UE_LOG(LogTemp, Warning, TEXT("TICK TOCK"));
}

ATank * ATankController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if(!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerControllerNot Posessing tank: %s"));
	}else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController  Posessing tank: %s"), *ControlledTank->GetName());
	}
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));
}
