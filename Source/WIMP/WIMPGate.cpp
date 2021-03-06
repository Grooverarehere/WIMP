// Fill out your copyright notice in the Description page of Project Settings.


#include "WIMPGate.h"
#include "WIMPCharacter.h"

// Sets default values
AWIMPGate::AWIMPGate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SK_DoorFrame = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SK_DoorFrame"));
	SK_DoorFrame->SetupAttachment(RootComponent);

	SM_DoorFrame_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_DoorFrame_1"));
	SM_DoorFrame_1->SetupAttachment(SK_DoorFrame,"Bone_door_R");

	SM_DoorFrame_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_DoorFrame_2"));
	SM_DoorFrame_2->SetupAttachment(SK_DoorFrame,"Bone_door_LSocket");
	bClosed = false;
}

// Called when the game starts or when spawned
void AWIMPGate::BeginPlay()
{
	Super::BeginPlay();
	ActivatorDoor_1->ActivatorCollision->OnComponentBeginOverlap.AddDynamic(this, &AWIMPGate::OnActivatorOverlap);
	ActivatorDoor_2->ActivatorCollision->OnComponentBeginOverlap.AddDynamic(this, &AWIMPGate::OnActivatorOverlap);
}

void AWIMPGate::OnActivatorOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AWIMPCharacter>(OtherActor))
	{
		if (!bClosed) {
			CloseDoor();
			bClosed = true;
		}
		else {
			OpenDoor();
			bClosed = false;
		}
		ActivatorDoor_1->Active = !ActivatorDoor_1->Active;
		ActivatorDoor_2->Active = !ActivatorDoor_2->Active;
		ActivatorDoor_1->ActivateActivator();
		ActivatorDoor_2->ActivateActivator();
	}
}

// Called every frame
void AWIMPGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



