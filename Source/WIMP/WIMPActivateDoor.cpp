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
	ActivatorCollision->SetGenerateOverlapEvents(true);

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
	ActivateActivator();
}



// Called every frame
void AWIMPActivateDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWIMPActivateDoor::ActivateActivator()
{
		if (!Active) {
			ActivatorCollision->SetCollisionResponseToChannels(ECR_Ignore);
			if (LaserArray.Num() > 0) {
				for (int i = 0; i < LaserArray.Num(); i++) {
					LaserArray[i]->DestroyComponent();
				}
				LaserArray.Empty();
			}
		}
		else {
			ActivatorCollision->SetCollisionResponseToChannels(ECR_Overlap);
			for (int i = 0; i < 4; i++) {
				if (PS_Laser->IsValidLowLevel()) {
					UParticleSystemComponent* laser = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PS_Laser, FVector(0, 0, 0), FRotator(0, 0, 0), true, EPSCPoolMethod::None, true);
					FString socket = "Socket";
					socket.AppendInt(i);
					laser->SetBeamSourcePoint(0, SM_Laser_1->GetSocketLocation(FName(socket)), 0);
					laser->SetBeamEndPoint(0, SM_Laser_2->GetSocketLocation(FName(socket)));
					LaserArray.Add(laser);
				}
			}
		}
	
}

