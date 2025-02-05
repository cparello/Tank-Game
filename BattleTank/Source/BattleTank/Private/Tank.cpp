// Fill out your copyright notice in the Description page of Project Settings.
#include "Tank.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "TankBarrel.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::GetHealthPercent() const
{
	return float(CurrentHealth) / float(StartingHealth);
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator,	AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	UE_LOG(LogTemp, Warning, TEXT("damageamount %f damagetoapply %f"), DamagePoints, DamageToApply)

	CurrentHealth -= DamageToApply;
	if(CurrentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Died"))
		OnDeath.Broadcast();
	}
		

	return DamageToApply;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}
