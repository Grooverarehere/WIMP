// Fill out your copyright notice in the Description page of Project Settings.


#include "WIMPMovableFloor.h"

// Sets default values
AWIMPMovableFloor::AWIMPMovableFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	MovementTimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("MovementTimelineComponent"));
}

// Called when the game starts or when spawned
void AWIMPMovableFloor::BeginPlay()
{
	Super::BeginPlay();
	InitPosition = GetActorLocation();
	if (E_Movement_Type == FloorMovementType::FRONT)
	{
		EndPosition = FVector(GetActorLocation().X + Distance, GetActorLocation().Y, GetActorLocation().Z);
	}
	if (E_Movement_Type == FloorMovementType::SLIDE)
	{
		EndPosition = FVector(GetActorLocation().X, GetActorLocation().Y + Distance, GetActorLocation().Z);
	}

	UpdateFunctionFloat.BindDynamic(this, &AWIMPMovableFloor::UpdateTimelineFunction);
	if (MovementTimelineComponent)
	{
		MovementTimelineComponent->AddInterpFloat(MovementTimelineCurve, UpdateFunctionFloat);
	}
}

void AWIMPMovableFloor::UpdateTimelineFunction(float Output)
{
	SetActorLocation(FMath::Lerp(InitPosition, EndPosition, Output));
}

// Called every frame
void AWIMPMovableFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetActorLocation().Equals(EndPosition))
	{
		MovementTimelineComponent->Reverse();
	}

	if (GetActorLocation().Equals(InitPosition))
	{
		MovementTimelineComponent->Play();
	}
}

