// Fill out your copyright notice in the Description page of Project Settings.


#include "WIMPElevator.h"
#include "WIMPCharacter.h"

// Sets default values
AWIMPElevator::AWIMPElevator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	ElavatorCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ElevatorCollision"));
	ElavatorCollision->SetupAttachment(RootComponent);
	ElavatorCollision->SetGenerateOverlapEvents(true);

	ElevatorTimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("ElevatorTimelineComponent"));

	Altitude = 300.f;
}

// Called when the game starts or when spawned
void AWIMPElevator::BeginPlay()
{
	Super::BeginPlay();
	InitPosition = GetActorLocation();
	EndPosition = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + Altitude);
	UpdateFunctionFloat.BindDynamic(this, &AWIMPElevator::UpdateTimelineFunction);
	if (ElevatorTimelineComponent)
	{
		ElevatorTimelineComponent->AddInterpFloat(ElevatorTimelineCurve,UpdateFunctionFloat);
	}
	ElavatorCollision->OnComponentBeginOverlap.AddDynamic(this, &AWIMPElevator::OnBeginOverlap);
	ElavatorCollision->OnComponentEndOverlap.AddDynamic(this, &AWIMPElevator::OnEndOverlap);
}

// Called every frame
void AWIMPElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWIMPElevator::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AWIMPCharacter* character = Cast<AWIMPCharacter>(OtherActor);
	if (character->IsValidLowLevel())
	{
		ElevatorTimelineComponent->Play();
	}
}

void AWIMPElevator::UpdateTimelineFunction(float Output)
{
	SetActorLocation(FMath::Lerp(InitPosition,EndPosition,Output));
}

void AWIMPElevator::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AWIMPCharacter* character = Cast<AWIMPCharacter>(OtherActor);
	if (character->IsValidLowLevel())
	{
		ElevatorTimelineComponent->Reverse();
	}
}
