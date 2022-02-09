// Fill out your copyright notice in the Description page of Project Settings.


#include "WIMPScoutDroid.h"

// Sets default values
AWIMPScoutDroid::AWIMPScoutDroid()
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
void AWIMPScoutDroid::BeginPlay()
{
	Super::BeginPlay();
	
	InitPosition = GetActorLocation();
	EndPosition= EndPosition = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z+Distance);
	UpdateFunctionFloat.BindDynamic(this, &AWIMPScoutDroid::UpdateTimelineFunction);
	if (MovementTimelineComponent)
	{
		MovementTimelineComponent->AddInterpFloat(MovementTimelineCurve, UpdateFunctionFloat);
	}
}

void AWIMPScoutDroid::UpdateTimelineFunction(float Output)
{
	SetActorLocation(FMath::Lerp(InitPosition, EndPosition, Output));
}

// Called every frame
void AWIMPScoutDroid::Tick(float DeltaTime)
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

