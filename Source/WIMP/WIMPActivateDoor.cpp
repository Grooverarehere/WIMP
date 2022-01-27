// Fill out your copyright notice in the Description page of Project Settings.


#include "WIMPActivateDoor.h"
#include "WIMPCharacter.h"

// Sets default values
AWIMPActivateDoor::AWIMPActivateDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActivatorCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ActivatorCollision"));
	ActivatorCollision->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void AWIMPActivateDoor::BeginPlay()
{
	Super::BeginPlay();
	ActivatorCollision->OnComponentBeginOverlap.AddDynamic(this,&AWIMPActivateDoor::OnBeginOverlap);
}

void AWIMPActivateDoor::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AWIMPCharacter>(OtherActor))
	{
		OperationGate->CloseDoor();
	}
}

// Called every frame
void AWIMPActivateDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

