// Fill out your copyright notice in the Description page of Project Settings.


#include "WIMPDog.h"

// Sets default values
AWIMPDog::AWIMPDog()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);*/

	WakeUpCollision = CreateDefaultSubobject<USphereComponent>(TEXT("WakeUpCollision"));
	WakeUpCollision->SetupAttachment(RootComponent);
	WakeUpCollision->SetSphereRadius(981.85f);
	WakeUpCollision->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void AWIMPDog::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AWIMPDog::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
