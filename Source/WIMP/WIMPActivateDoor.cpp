// Fill out your copyright notice in the Description page of Project Settings.


#include "WIMPActivateDoor.h"
#include "WIMPCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWIMPActivateDoor::AWIMPActivateDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	ActivatorCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ActivatorCollision"));
	ActivatorCollision->SetupAttachment(RootComponent);
	ActivatorCollision->SetGenerateOverlapEvents(false);

	SM_Laser_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Laser_1"));
	SM_Laser_1->SetupAttachment(RootComponent);
	SM_Laser_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Laser_2"));
	SM_Laser_2->SetupAttachment(RootComponent);
	Active = false;
}

// Called when the game starts or when spawned
void AWIMPActivateDoor::BeginPlay()
{
	Super::BeginPlay();
	ActivatorCollision->OnComponentBeginOverlap.AddDynamic(this,&AWIMPActivateDoor::OnBeginOverlap);
	for (int i = 0; i < 4; i++)
	{
		UParticleSystemComponent *laser = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PS_Laser, FVector(0, 0, 0), FRotator(0, 0, 0), true, EPSCPoolMethod::None, false);
		laser->SetBeamSourcePoint(0, SM_Laser_1->GetSocketLocation("Socket" + i),0);
		laser->SetBeamEndPoint(0, SM_Laser_2->GetSocketLocation("Socket" + i));
		LaserArray.Add(laser);
		
	}
	
	ActivateActivator(Active);
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

void AWIMPActivateDoor::ActivateActivator(bool value)
{
	UE_LOG(LogTemp, Warning, TEXT("value:%s"),value? "true" : "false");
	ActivatorCollision->SetGenerateOverlapEvents(value);
	for (int i = 0; i < LaserArray.Num(); i++)
	{
		LaserArray[i]->Activate(value);
	}
}

