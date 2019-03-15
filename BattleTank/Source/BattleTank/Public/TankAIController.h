// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

//forward declaration
class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float AcceptanceRadius = 8000;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;

private:
	UFUNCTION()
	void OnPossessedTankDeath();
};
