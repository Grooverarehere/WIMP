// Fill out your copyright notice in the Description page of Project Settings.


#include "WIMPBattleDroid.h"

// Sets default values
AWIMPBattleDroid::AWIMPBattleDroid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

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
	//PS_Jet_Front->SetRelativeScale3D(ActivatePlasma);

	PS_Jet_Front_Right = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PS_Jet_Front_Right"));
	PS_Jet_Front_Right->SetupAttachment(Mesh);
	//PS_Jet_Front_Right->SetRelativeScale3D(ActivatePlasma);

	PS_Jet_Front_Left = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PS_Jet_Front_Left"));
	PS_Jet_Front_Left->SetupAttachment(Mesh);
	//PS_Jet_Front_Left->SetRelativeScale3D(ActivatePlasma);

	PS_Jet_Back = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PS_Jet_Back"));
	PS_Jet_Back->SetupAttachment(Mesh);
	//PS_Jet_Back->SetRelativeScale3D(ActivatePlasma);

	PS_Jet_Back_Right = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PS_Jet_Back_Right"));
	PS_Jet_Back_Right->SetupAttachment(Mesh);
	//PS_Jet_Back_Right->SetRelativeScale3D(ActivatePlasma);

	PS_Jet_Back_Left = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PS_Jet_Back_Left"));
	PS_Jet_Back_Left->SetupAttachment(Mesh);
	//PS_Jet_Back_Left->SetRelativeScale3D(ActivatePlasma);

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
	RateCharge = 3.0f;
}

// Called when the game starts or when spawned
void AWIMPBattleDroid::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(ChargeHandle, this, &AWIMPBattleDroid::Charge, RateCharge, true);
	Mesh->SetScalarParameterValueOnMaterials("Emissive_Power", 1.0f);
}

void AWIMPBattleDroid::Charge()
{
	PS_Lighting->ActivateSystem();
	if (ProjectileClass)
	{
		GetWorldTimerManager().SetTimer(LaunchHandle, this, &AWIMPBattleDroid::LaunchProjectile, 0.5f, false);
	}
}


void AWIMPBattleDroid::LaunchProjectile()
{
	UWorld* World = GetWorld();
	if (World)
	{

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		AWIMPProjectile* projectile = World->SpawnActor<AWIMPProjectile>(ProjectileClass, PS_Lighting->GetComponentLocation(), GetActorRotation(), SpawnParams);
	}
}

// Called every frame
void AWIMPBattleDroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

