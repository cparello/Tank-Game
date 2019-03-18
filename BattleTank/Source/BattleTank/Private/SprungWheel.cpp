// Copyright Chris Parello

#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassWheelConstraint"));
	SetRootComponent(MassWheelConstraint);

	Axel = CreateDefaultSubobject<USphereComponent>(FName("Axel"));
	Axel->SetupAttachment(MassWheelConstraint);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axel);
	
	AxelWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxelWheelConstraint"));
	AxelWheelConstraint->SetupAttachment(Axel);
}

void ASprungWheel::SetupConstraint()
{
	if(!GetAttachParentActor()){return;}

	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());

	if (!BodyRoot) { return; }

	MassWheelConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axel, NAME_None);
	AxelWheelConstraint->SetConstrainedComponents(Axel, NAME_None, Wheel, NAME_None);

	return;
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	SetupConstraint();
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	Wheel->AddForce(Axel->GetForwardVector() * ForceMagnitude);
}

