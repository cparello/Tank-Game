// Fill out your copyright notice in the Description page of Project Settings.

#include "TankController.h"
#include "Runtime/Engine/Classes/GameFramework/Pawn.h"



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
