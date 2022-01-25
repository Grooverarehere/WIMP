// Fill out your copyright notice in the Description page of Project Settings.


#include "WIMPVanishingFloor.h"
#include "Materials/Material.h"

// Sets default values
AWIMPVanishingFloor::AWIMPVanishingFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	MaterializeTimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("MaterializeTimelineComponent"));
}

// Called when the game starts or when spawned
void AWIMPVanishingFloor::BeginPlay()
{
	Super::BeginPlay();
	MID = Mesh->CreateDynamicMaterialInstance(0, Mesh->GetMaterial(0));
	UpdateFunctionFloat.BindDynamic(this, &AWIMPVanishingFloor::UpdateTimelineFunction);
	if (MaterializeTimelineComponent)
	{
		MaterializeTimelineComponent->AddInterpFloat(MaterializeTimelineCurve, UpdateFunctionFloat);
	}
	GetWorldTimerManager().SetTimer(VanishHandle, this, &AWIMPVanishingFloor::Vanish, TimeToVanish, false);
}

void AWIMPVanishingFloor::UpdateTimelineFunction(float Output)
{
	MID->SetScalarParameterValue("Materialize Amount", Output);
	if (Output == 1.f)
	{
		GetWorldTimerManager().SetTimer(VanishHandle, this, &AWIMPVanishingFloor::Vanish, TimeToVanish, false);
	}
	if (Output >= 0.5f)
	{
		Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	if (Output <= 0.5f)
	{
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	if (Output == 0.f)
	{
		GetWorldTimerManager().SetTimer(VisibleHandle, this, &AWIMPVanishingFloor::Visible, TimeToVisible, false);
	}
	
}

void AWIMPVanishingFloor::Vanish()
{
	MaterializeTimelineComponent->Reverse();
	GetWorldTimerManager().ClearTimer(VisibleHandle);
}

void AWIMPVanishingFloor::Visible()
{
	MaterializeTimelineComponent->Play();
	GetWorldTimerManager().ClearTimer(VanishHandle);
}

// Called every frame
void AWIMPVanishingFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

