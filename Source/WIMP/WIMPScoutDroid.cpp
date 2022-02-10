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

	Light = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Light"));
	Light->SetupAttachment(Mesh);

	Jet_Front = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Jet_Front"));
	Jet_Front->SetupAttachment(Mesh);

	Jet_Front_Right = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Jet_Front_Right"));
	Jet_Front_Right->SetupAttachment(Mesh);

	Jet_Front_Left = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Jet_Front_Left"));
	Jet_Front_Left->SetupAttachment(Mesh);

	Jet_Back = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Jet_Back"));
	Jet_Back->SetupAttachment(Mesh);

	Jet_Back_Right = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Jet_Back_Right"));
	Jet_Back_Right->SetupAttachment(Mesh);

	Jet_Back_Left = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Jet_Back_Left"));
	Jet_Back_Left->SetupAttachment(Mesh);

	PS_Jet_Front = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PS_Jet_Front"));
	PS_Jet_Front->SetupAttachment(Mesh);
	

	PS_Jet_Front_Right = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PS_Jet_Front_Right"));
	PS_Jet_Front_Right->SetupAttachment(Mesh);
	

	PS_Jet_Front_Left = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PS_Jet_Front_Left"));
	PS_Jet_Front_Left->SetupAttachment(Mesh);
	

	PS_Jet_Back = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PS_Jet_Back"));
	PS_Jet_Back->SetupAttachment(Mesh);
	

	PS_Jet_Back_Right = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PS_Jet_Back_Right"));
	PS_Jet_Back_Right->SetupAttachment(Mesh);
	

	PS_Jet_Back_Left = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PS_Jet_Back_Left"));
	PS_Jet_Back_Left->SetupAttachment(Mesh);
	MovementTimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("MovementTimelineComponent"));
}

// Called when the game starts or when spawned
void AWIMPScoutDroid::BeginPlay()
{
	Super::BeginPlay();
	
	InitPosition = Mesh->GetRelativeLocation();
	EndPosition = FVector(Mesh->GetRelativeLocation().X, Mesh->GetRelativeLocation().Y, Mesh->GetRelativeLocation().Z+Distance);
	UpdateFunctionFloat.BindDynamic(this, &AWIMPScoutDroid::UpdateTimelineFunction);
	FinishedFunctionFloat.BindUFunction(this,"FinishedTimelineFunction");
	if (MovementTimelineComponent)
	{
		MovementTimelineComponent->AddInterpFloat(MovementTimelineCurve, UpdateFunctionFloat);
		MovementTimelineComponent->SetTimelineFinishedFunc(FinishedFunctionFloat);
	}
	MovementTimelineComponent->Play();
	E_Movement_Type = MovementType::UP_START;
	Mesh->SetScalarParameterValueOnMaterials("Emissive_Power", 1.0f);
	Light->SetScalarParameterValueOnMaterials("Emissive_Power", 1.0f);
	Jet_Front->SetScalarParameterValueOnMaterials("Emissive_Power", 1.0f);
	Jet_Front_Right->SetScalarParameterValueOnMaterials("Emissive_Power", 1.0f);
	Jet_Front_Left->SetScalarParameterValueOnMaterials("Emissive_Power", 1.0f);
	Jet_Back->SetScalarParameterValueOnMaterials("Emissive_Power", 1.0f);
	Jet_Back_Right->SetScalarParameterValueOnMaterials("Emissive_Power", 1.0f);
	Jet_Back_Left->SetScalarParameterValueOnMaterials("Emissive_Power", 1.0f);
}

void AWIMPScoutDroid::UpdateTimelineFunction(float Output)
{
	Mesh->SetRelativeLocation(FMath::Lerp(InitPosition, EndPosition, Output));
}

void AWIMPScoutDroid::FinishedTimelineFunction()
{
		switch (E_Movement_Type)
		{
		case MovementType::UP_START:
			
				MovementTimelineComponent->Reverse();
				E_Movement_Type = MovementType::UP_END;
				break;
		case MovementType::UP_END:
			
				EndPosition = FVector(Mesh->GetRelativeLocation().X, Mesh->GetRelativeLocation().Y + Distance, Mesh->GetRelativeLocation().Z);
				E_Movement_Type = MovementType::SLIDE_START;
				MovementTimelineComponent->Play();
			
			break;
		case MovementType::SLIDE_START:
			
				MovementTimelineComponent->Reverse();
				E_Movement_Type = MovementType::SLIDE_END;
				break;
		case MovementType::SLIDE_END:
			
				EndPosition = FVector(Mesh->GetRelativeLocation().X + Distance, Mesh->GetRelativeLocation().Y, Mesh->GetRelativeLocation().Z);
				E_Movement_Type = MovementType::FRONT_START;
				MovementTimelineComponent->Play();
			break;
		case MovementType::FRONT_START:
			
				MovementTimelineComponent->Reverse();
				E_Movement_Type = MovementType::FRONT_END;
				break;
		case MovementType::FRONT_END:
				EndPosition = EndPosition = FVector(Mesh->GetRelativeLocation().X, Mesh->GetRelativeLocation().Y, Mesh->GetRelativeLocation().Z + Distance);
				E_Movement_Type = MovementType::UP_START;
				MovementTimelineComponent->Play();
			
			break;
		}
}

// Called every frame
void AWIMPScoutDroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

