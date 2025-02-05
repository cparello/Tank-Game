// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"


UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float AcceptanceRadius = 8000;

private:
	UFUNCTION()
	void OnPossessedTankDeath(); 
	
	virtual void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
