// Fill out your copyright notice in the Description page of Project Settings.


#include "WIMPScoutDroid.h"
#include "WIMPCharacter.h"

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
	

	ActivatePlasma = FVector(1.f, 1.f, 1.f);
	DeactivatePlasma = FVector(0.7f, 0.7f, 0.4f);

	PS_Jet_Front = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PS_Jet_Front"));
	PS_Jet_Front->SetupAttachment(Mesh);
	PS_Jet_Front->SetRelativeScale3D(ActivatePlasma);

	PS_Jet_Front_Right = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PS_Jet_Front_Right"));
	PS_Jet_Front_Right->SetupAttachment(Mesh);
	PS_Jet_Front_Right->SetRelativeScale3D(ActivatePlasma);

	PS_Jet_Front_Left = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PS_Jet_Front_Left"));
	PS_Jet_Front_Left->SetupAttachment(Mesh);
	PS_Jet_Front_Left->SetRelativeScale3D(ActivatePlasma);

	PS_Jet_Back = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PS_Jet_Back"));
	PS_Jet_Back->SetupAttachment(Mesh);
	PS_Jet_Back->SetRelativeScale3D(ActivatePlasma);

	PS_Jet_Back_Right = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PS_Jet_Back_Right"));
	PS_Jet_Back_Right->SetupAttachment(Mesh);
	PS_Jet_Back_Right->SetRelativeScale3D(ActivatePlasma);

	PS_Jet_Back_Left = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PS_Jet_Back_Left"));
	PS_Jet_Back_Left->SetupAttachment(Mesh);
	PS_Jet_Back_Left->SetRelativeScale3D(ActivatePlasma);

	PS_Tesla_Top = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PS_Tesla_Top"));
	PS_Tesla_Top->SetupAttachment(Mesh);
	

	PS_Tesla_Bottom = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PS_Tesla_Bottom"));
	PS_Tesla_Bottom->SetupAttachment(Mesh);
	

	PS_Tesla_Back = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PS_Tesla_Back"));
	PS_Tesla_Back->SetupAttachment(Mesh);
	

	PS_Tesla_Right = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PS_Tesla_Right"));
	PS_Tesla_Right->SetupAttachment(Mesh);
	

	PS_Tesla_Left = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PS_Tesla_Left"));
	PS_Tesla_Left->SetupAttachment(Mesh);
	

	PS_Lighting = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PS_Lighting"));
	PS_Lighting->SetupAttachment(Mesh);
	PS_Lighting->bAutoActivate = false;

	MovementTimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("MovementTimelineComponent"));

	DroidDetection = CreateDefaultSubobject<USphereComponent>(TEXT("DroidDetection"));
	DroidDetection->SetupAttachment(Mesh);
	DroidDetection->SetGenerateOverlapEvents(true);
	DroidDetection->OnComponentBeginOverlap.AddDynamic(this, &AWIMPScoutDroid::OnDetection);
	DroidDetection->OnComponentEndOverlap.AddDynamic(this, &AWIMPScoutDroid::OnStopDetection);

	DroidHit = CreateDefaultSubobject<USphereComponent>(TEXT("DroidHit"));
	DroidHit->SetupAttachment(Mesh);
	DroidHit->SetGenerateOverlapEvents(true);
	DroidHit->OnComponentBeginOverlap.AddDynamic(this, &AWIMPScoutDroid::OnHit);
	bOnHit = false;
}

// Called when the game starts or when spawned
void AWIMPScoutDroid::BeginPlay()
{
	Super::BeginPlay();
	
	
	UpdateFunctionFloat.BindDynamic(this, &AWIMPScoutDroid::UpdateTimelineFunction);
	FinishedFunctionFloat.BindUFunction(this,"FinishedTimelineFunction");
	if (MovementTimelineComponent)
	{
		MovementTimelineComponent->AddInterpFloat(MovementTimelineCurve, UpdateFunctionFloat);
		MovementTimelineComponent->SetTimelineFinishedFunc(FinishedFunctionFloat);
	}
	
	Mesh->SetScalarParameterValueOnMaterials("Emissive_Power", 1.0f);
	Light->SetScalarParameterValueOnMaterials("Emissive_Power", 1.0f);
	Jet_Front->SetScalarParameterValueOnMaterials("Emissive_Power", 1.0f);
	Jet_Front_Right->SetScalarParameterValueOnMaterials("Emissive_Power", 1.0f);
	Jet_Front_Left->SetScalarParameterValueOnMaterials("Emissive_Power", 1.0f);
	Jet_Back->SetScalarParameterValueOnMaterials("Emissive_Power", 1.0f);
	Jet_Back_Right->SetScalarParameterValueOnMaterials("Emissive_Power", 1.0f);
	Jet_Back_Left->SetScalarParameterValueOnMaterials("Emissive_Power", 1.0f);
	
	InitDroid();
}

void AWIMPScoutDroid::UpdateTimelineFunction(float Output)
{
	Mesh->SetRelativeLocation(FMath::Lerp(InitPosition, EndPosition, Output));
}

void AWIMPScoutDroid::FinishedTimelineFunction()
{
	switch (E_Droid_Type)
	{
	case DroidType::THREE_MOVEMENT:

		switch (E_Movement_Type)
		{
		case MovementType::UP_START:

			MovementTimelineComponent->Reverse();
			E_Movement_Type = MovementType::UP_END;
			ChangePlasma();
			break;
		case MovementType::UP_END:

			EndPosition = FVector(Mesh->GetRelativeLocation().X, Mesh->GetRelativeLocation().Y + Distance, Mesh->GetRelativeLocation().Z);
			E_Movement_Type = MovementType::SLIDE_START;
			MovementTimelineComponent->Play();
			ChangePlasma();
			break;
		case MovementType::SLIDE_START:

			MovementTimelineComponent->Reverse();
			E_Movement_Type = MovementType::SLIDE_END;
			ChangePlasma();
			break;
		case MovementType::SLIDE_END:

			EndPosition = FVector(Mesh->GetRelativeLocation().X + Distance, Mesh->GetRelativeLocation().Y, Mesh->GetRelativeLocation().Z);
			E_Movement_Type = MovementType::FRONT_START;
			MovementTimelineComponent->Play();
			ChangePlasma();
			break;
		case MovementType::FRONT_START:

			MovementTimelineComponent->Reverse();
			E_Movement_Type = MovementType::FRONT_END;
			ChangePlasma();
			break;
		case MovementType::FRONT_END:
			EndPosition = EndPosition = FVector(Mesh->GetRelativeLocation().X, Mesh->GetRelativeLocation().Y, Mesh->GetRelativeLocation().Z + Distance);
			E_Movement_Type = MovementType::UP_START;
			MovementTimelineComponent->Play();
			ChangePlasma();
			break;
		}
		break;
	case DroidType::SLIDE_MOVEMENT:
		if (E_Movement_Type == MovementType::SLIDE_START)
		{
			MovementTimelineComponent->Reverse();
			E_Movement_Type = MovementType::SLIDE_END;
			ChangePlasma();
		}
		else
		{
			
			E_Movement_Type = MovementType::SLIDE_START;
			MovementTimelineComponent->Play();
			ChangePlasma();
		}
		break;
	case DroidType::UP_MOVEMENT:
		if (E_Movement_Type == MovementType::UP_START)
		{
			MovementTimelineComponent->Reverse();
			E_Movement_Type = MovementType::UP_END;
			ChangePlasma();
		}
		else
		{
			E_Movement_Type = MovementType::UP_START;
			MovementTimelineComponent->Play();
			ChangePlasma();
		}
		break;
	}
}

void AWIMPScoutDroid::ChangePlasma()
{
	
	switch (E_Movement_Type)
	{
	case MovementType::UP_START:
		PS_Jet_Front->SetRelativeScale3D(DeactivatePlasma);
		PS_Jet_Front_Right->SetRelativeScale3D(ActivatePlasma);
		PS_Jet_Front_Left->SetRelativeScale3D(ActivatePlasma);
		PS_Jet_Back->SetRelativeScale3D(ActivatePlasma);
		PS_Jet_Back_Right->SetRelativeScale3D(DeactivatePlasma);
		PS_Jet_Back_Left->SetRelativeScale3D(DeactivatePlasma);
		break;
	case MovementType::UP_END:
		PS_Jet_Front->SetRelativeScale3D(ActivatePlasma);
		PS_Jet_Front_Right->SetRelativeScale3D(DeactivatePlasma);
		PS_Jet_Front_Left->SetRelativeScale3D(DeactivatePlasma);
		PS_Jet_Back->SetRelativeScale3D(DeactivatePlasma);
		PS_Jet_Back_Right->SetRelativeScale3D(ActivatePlasma);
		PS_Jet_Back_Left->SetRelativeScale3D(ActivatePlasma);
		break;
	case MovementType::SLIDE_START:
		PS_Jet_Front->SetRelativeScale3D(DeactivatePlasma);
		PS_Jet_Front_Right->SetRelativeScale3D(DeactivatePlasma);
		PS_Jet_Front_Left->SetRelativeScale3D(ActivatePlasma);
		PS_Jet_Back->SetRelativeScale3D(DeactivatePlasma);
		PS_Jet_Back_Right->SetRelativeScale3D(DeactivatePlasma);
		PS_Jet_Back_Left->SetRelativeScale3D(ActivatePlasma);
		break;
	case MovementType::SLIDE_END:
		PS_Jet_Front->SetRelativeScale3D(DeactivatePlasma);
		PS_Jet_Front_Right->SetRelativeScale3D(ActivatePlasma);
		PS_Jet_Front_Left->SetRelativeScale3D(DeactivatePlasma);
		PS_Jet_Back->SetRelativeScale3D(DeactivatePlasma);
		PS_Jet_Back_Right->SetRelativeScale3D(ActivatePlasma);
		PS_Jet_Back_Left->SetRelativeScale3D(DeactivatePlasma);
		break;
	case MovementType::FRONT_START:
		PS_Jet_Front->SetRelativeScale3D(DeactivatePlasma);
		PS_Jet_Front_Right->SetRelativeScale3D(DeactivatePlasma);
		PS_Jet_Front_Left->SetRelativeScale3D(DeactivatePlasma);
		PS_Jet_Back->SetRelativeScale3D(ActivatePlasma);
		PS_Jet_Back_Right->SetRelativeScale3D(ActivatePlasma);
		PS_Jet_Back_Left->SetRelativeScale3D(ActivatePlasma);
		break;
	case MovementType::FRONT_END:
		PS_Jet_Front->SetRelativeScale3D(ActivatePlasma);
		PS_Jet_Front_Right->SetRelativeScale3D(ActivatePlasma);
		PS_Jet_Front_Left->SetRelativeScale3D(ActivatePlasma);
		PS_Jet_Back->SetRelativeScale3D(DeactivatePlasma);
		PS_Jet_Back_Right->SetRelativeScale3D(DeactivatePlasma);
		PS_Jet_Back_Left->SetRelativeScale3D(DeactivatePlasma);
		break;
	}
}

// Called every frame
void AWIMPScoutDroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AWIMPScoutDroid::OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AWIMPCharacter* character = Cast<AWIMPCharacter>(OtherActor);
	if (character->IsValidLowLevel()&&!bOnHit)
	{
		bOnHit = true;
		character->DestroyTimelineComponent->Play();
		PS_Lighting->ActivateSystem();
		
	}
}

void AWIMPScoutDroid::OnDetection(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AWIMPCharacter* character = Cast<AWIMPCharacter>(OtherActor);
	if (character->IsValidLowLevel())
	{
		if (E_Movement_Type == MovementType::UP_START || E_Movement_Type == MovementType::SLIDE_START || E_Movement_Type == MovementType::FRONT_START) {
			MovementTimelineComponent->Play();
			ChangePlasma();
		}
		else {
			MovementTimelineComponent->Reverse();
			ChangePlasma();
		}
	}
}

void AWIMPScoutDroid::OnStopDetection(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AWIMPCharacter* character = Cast<AWIMPCharacter>(OtherActor);
	if (character->IsValidLowLevel())
	{
		MovementTimelineComponent->Stop();
		bOnHit = false;
	}
}

void AWIMPScoutDroid::InitDroid()
{
	InitPosition = Mesh->GetRelativeLocation();
	switch (E_Droid_Type)
	{
	case DroidType::THREE_MOVEMENT:
		EndPosition = FVector(Mesh->GetRelativeLocation().X, Mesh->GetRelativeLocation().Y, Mesh->GetRelativeLocation().Z + Distance);
		E_Movement_Type = MovementType::UP_START;
		break;
	case DroidType::SLIDE_MOVEMENT:
		EndPosition = FVector(Mesh->GetRelativeLocation().X, Mesh->GetRelativeLocation().Y + Distance, Mesh->GetRelativeLocation().Z);
		E_Movement_Type = MovementType::SLIDE_START;
		break;
	case DroidType::UP_MOVEMENT:
		EndPosition = FVector(Mesh->GetRelativeLocation().X, Mesh->GetRelativeLocation().Y, Mesh->GetRelativeLocation().Z + Distance);
		E_Movement_Type = MovementType::UP_START;
		break;
	}
	
}

