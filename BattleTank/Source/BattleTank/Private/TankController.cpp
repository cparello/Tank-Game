// Fill out your copyright notice in the Description page of Project Settings.

#include "TankController.h"

void ATankController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector OutHitLocation;

	if(GetSightRayHitLocation(OutHitLocation)) // has "side effect is going to line trace
	{
		UE_LOG(LogTemp, Warning, TEXT("hit location %s"), *OutHitLocation.ToString());
			//TODO tell take to aim at this oint
	}

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
//get world location of line trace crosshair, true if hits landscape
bool ATankController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s "), *ScreenLocation.ToString());


	OutHitLocation = FVector(1.0f);
	return true;
}
