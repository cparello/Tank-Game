// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//AimTowardsCrosshair();
	//UE_LOG(LogTemp, Warning, TEXT("TICK TOCK"));

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());
	if(PlayerTank)
	{
		//TODO move towards player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		//fire
		ControlledTank->Fire();//TODO dont fire every frame
	}
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

