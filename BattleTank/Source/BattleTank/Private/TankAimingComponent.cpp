// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	//if (!ensure(Barrel && Turret)) { return; }
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; //TODO should this tick?

	// ...
}


void UTankAimingComponent::AimAt(FVector OutHitLocation)
{
	if (!ensure(Barrel)) { return; }
	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// calculate the out launch velocity
	if(UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, OutHitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector TargetAimDirection)
{
	if(!ensure(Barrel) || !ensure(Turret)){ return; }

	// workout offset of aim and barrel position
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = TargetAimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	if(FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
	
}

void UTankAimingComponent::Fire()
{
	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming)
	{
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		//spawn a projectile
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
		if (!ensure(Projectile)) { return; }
		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();

		RoundsLeft--;
	}
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }

	// workout offset of aim and barrel position
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01);
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType,	FActorComponentTickFunction* ThisTickFunction)
{
	if(RoundsLeft <= 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT(" AMMO %i"), RoundsLeft)
		FiringState = EFiringState::OutOfAmmo;
	}
	else if((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		//UE_LOG(LogTemp, Warning, TEXT(" Reloading"))
		FiringState = EFiringState::Reloading;
	}else if(IsBarrelMoving())
	{
		//UE_LOG(LogTemp, Warning, TEXT(" Aiming"))
		FiringState = EFiringState::Aiming;
	}else
	{
		//UE_LOG(LogTemp, Warning, TEXT(" Locked "))
		FiringState = EFiringState::Locked;
	}
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}
