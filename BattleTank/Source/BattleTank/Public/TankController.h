// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankController : public APlayerController
{
	GENERATED_BODY()
	
	
public:
	void AimTowardsCrosshair();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	ATank * GetControlledTank() const;
	
	virtual void BeginPlay() override;
};
