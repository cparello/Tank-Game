// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//AimTowardsCrosshair();
	//UE_LOG(LogTemp, Warning, TEXT("TICK TOCK"));

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	if (!ensure(PlayerTank && ControlledTank)) {return;}
	MoveToActor(PlayerTank, AcceptanceRadius);

	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();//TODO dont fire every frame
	}
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

