// Fill out your copyright notice in the Description page of Project Settings.


#include "WIMPHighJump.h"
#include "WIMPCharacter.h"

// Sets default values
AWIMPHighJump::AWIMPHighJump()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	JumpCollision = CreateDefaultSubobject<USphereComponent>(TEXT("JumpCollision"));
	JumpCollision->SetupAttachment(RootComponent);
	JumpCollision->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void AWIMPHighJump::BeginPlay()
{
	Super::BeginPlay();
	JumpCollision->OnComponentBeginOverlap.AddDynamic(this, &AWIMPHighJump::OnBeginOverlap);
}

void AWIMPHighJump::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AWIMPCharacter* character = Cast<AWIMPCharacter>(OtherActor);
	if (character->IsValidLowLevel())
	{
		FVector jumpImpulse(0.f, 0.f, 1500.f);
		character->LaunchCharacter(jumpImpulse, false, false);
	}
}

// Called every frame
void AWIMPHighJump::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

