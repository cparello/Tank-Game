// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//AimTowardsCrosshair();
	//UE_LOG(LogTemp, Warning, TEXT("TICK TOCK"));
	if(GetPlayerTank())
	{
		//TODO move towards player

		//aim at player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		//fire
	}
}
ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerControllerNot  AI Posessing tank: %s"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController  AI Posessing tank: %s"), *ControlledTank->GetName());
	}
	UE_LOG(LogTemp, Warning, TEXT("PlayerController AI  Begin Play"));

	auto PlayerPawn = GetPlayerTank();
	if (!PlayerPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerPawn  Posessing tank: %s"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerPawn  Posessing tank: %s"), *PlayerPawn->GetName());
	}
	UE_LOG(LogTemp, Warning, TEXT("PlayerPawn   Begin Play"));
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if(!PlayerPawn)	{		return nullptr;	}
	return Cast<ATank>(PlayerPawn);
}
