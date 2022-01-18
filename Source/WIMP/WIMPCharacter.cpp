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

	// Create a camera...
	AbsoluteCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("AbsoluteCameraComponent"));
	//TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	AbsoluteCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	ZoomCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("ZoomCameraComponent"));
	ZoomCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	

	ZoomTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("ZoomTimelineComp"));
	PCTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("PCTimelineComp"));

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	m_InitOrthoWidth = 5000.f;
}

void AWIMPCharacter::BeginPlay()
{
	Super::BeginPlay();
	AbsoluteCameraComponent->OrthoWidth = m_InitOrthoWidth;
	AbsoluteCameraPos = AbsoluteCameraComponent->GetComponentLocation();
	UpdateZoomFloat.BindDynamic(this, &AWIMPCharacter::UpdateZoomComp);
	UpdatePositionFloat.BindDynamic(this, &AWIMPCharacter::UpdateTimelinePosition);
	OnTimelinePositionFinished.BindUFunction(this, "FinishedTimelinePosition");
	if (ZoomTimelineComp)
	{
		ZoomTimelineComp->AddInterpFloat(ZoomTimeLineCurve, UpdateZoomFloat);
	}
	if (PCTimelineComp)
	{
		PCTimelineComp->AddInterpFloat(PositionTimelineCurve, UpdatePositionFloat);
		PCTimelineComp->SetTimelineFinishedFunc(OnTimelinePositionFinished);
	}
}

void AWIMPCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	
}

void AWIMPCharacter::UpdateZoomComp(float Output)
{
	AbsoluteCameraComponent->OrthoWidth = m_InitOrthoWidth * Output;
}

void AWIMPCharacter::UpdateTimelinePosition(float Output)
{
	AbsoluteCameraComponent->SetWorldLocation(FMath::Lerp(AbsoluteCameraPos,ZoomCameraPos , Output));
}

void AWIMPCharacter::FinishedTimelinePosition()
{
	if (bZoom) {
		AbsoluteCameraComponent->AttachToComponent(CameraBoom, FAttachmentTransformRules::KeepWorldTransform);
	}
	else {
		AbsoluteCameraComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}
	
}

void AWIMPCharacter::ChangeCamera()
{
	if (bZoom)
	{
		bZoom = false;
		ZoomTimelineComp->Reverse();
		ZoomCameraPos = AbsoluteCameraComponent->GetComponentLocation();
		PCTimelineComp->Reverse();
		
	}
	else
	{
		bZoom = true;
		ZoomTimelineComp->Play();
		ZoomCameraPos=ZoomCameraComponent->GetComponentLocation();
		PCTimelineComp->Play();
	}
}
