// Copyright Epic Games, Inc. All Rights Reserved.

#include "WIMPCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"

AWIMPCharacter::AWIMPCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	ZoomCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("ZoomCameraComponent"));
	ZoomCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	
	MaterializeTimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("MaterializeTimelineComponent"));
	
	SpawnEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SpawnEffect"));
	SpawnEffect->SetupAttachment(RootComponent);
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
}

void AWIMPCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Hair=GetMesh()->CreateDynamicMaterialInstance(0, GetMesh()->GetMaterial(0));
	Skin=GetMesh()->CreateDynamicMaterialInstance(1, GetMesh()->GetMaterial(1));
	Outfit=GetMesh()->CreateDynamicMaterialInstance(2, GetMesh()->GetMaterial(2));
	UpdateFunctionFloat.BindDynamic(this, &AWIMPCharacter::UpdateTimelineFunction);
	if (MaterializeTimelineComponent)
	{
		MaterializeTimelineComponent->AddInterpFloat(MaterializeTimelineCurve, UpdateFunctionFloat);
	}
	MaterializeTimelineComponent->Play();
}

void AWIMPCharacter::UpdateTimelineFunction(float Output)
{
	Hair->SetScalarParameterValue("Materialize Amount", Output);
	Skin->SetScalarParameterValue("Materialize Amount", Output);
	Outfit->SetScalarParameterValue("Materialize Amount", Output);
	
}

void AWIMPCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	UE_LOG(LogTemp, Warning, TEXT("Speed:%f"),GetCharacterMovement()->MaxWalkSpeed);
	
}
