// Fill out your copyright notice in the Description page of Project Settings.
#include "TankController.h"
#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector OutHitLocation;

	if(GetSightRayHitLocation(OutHitLocation)) // has "side effect is going to line trace
	{
		AimingComponent->AimAt(OutHitLocation);
	}
}

void ATankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
	//UE_LOG(LogTemp, Warning, TEXT("TICK TOCK"));
}

void ATankController::BeginPlay()
{
	Super::BeginPlay();

	if(!GetPawn()) return;

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
		FoundAimingComponent(AimingComponent);
	
}

void ATankController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		//subscribe death
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankController::OnPossessedTankDeath);
	}
}

void ATankController::OnPossessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("death"))
		if (!GetPawn())
		{
			return;
		}
	StartSpectatingOnly();
}

bool ATankController::GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const
{
	//"De-project" the screen position of the crosshair to a world direction
	FVector CameraWorldLocation; // to be discarded but is required
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, OutLookDirection);
}

//get world location of line trace crosshair, true if hits landscape
bool ATankController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//find the crosshair position in pixel coords
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	//UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s "), *ScreenLocation.ToString());

	FVector OutLookDirection;
	if(GetLookDirection(ScreenLocation, OutLookDirection))
	{
		//line trace along look direction
		//UE_LOG(LogTemp, Warning, TEXT("Lookdirection: %s "), *OutLookDirection.ToString());
		return GetLookVectorHitDirection(OutLookDirection, OutHitLocation);
	}
	//OutHitLocation = FVector(1.0f);
	return false;
}

bool ATankController::GetLookVectorHitDirection(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if(GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Camera))
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	OutHitLocation = FVector(0);
	return false;
}