// Fill out your copyright notice in the Description page of Project Settings.


#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Physics Constraint"));
	SetRootComponent(PhysicsConstraint);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(PhysicsConstraint);

	AxleConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axle Constraint"));
	AxleConstraint->SetupAttachment(Axle);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axle);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	SetupConstraint();
}

void ASprungWheel::SetupConstraint()
{
	if (!GetAttachParentActor()) return;
	auto BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) return;
	PhysicsConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
	AxleConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

