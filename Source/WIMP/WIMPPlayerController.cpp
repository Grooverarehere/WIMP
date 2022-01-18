// Copyright Epic Games, Inc. All Rights Reserved.

#include "WIMPPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "WIMPCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"

AWIMPPlayerController::AWIMPPlayerController()
{
	
}

void AWIMPPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

}

void AWIMPPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveForward", this, &AWIMPPlayerController::ForwardMovement);
	InputComponent->BindAxis("MoveRight", this, &AWIMPPlayerController::RightMovement);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AWIMPPlayerController::Jump);
	InputComponent->BindAction("Run", IE_Pressed, this, &AWIMPPlayerController::Run);
	InputComponent->BindAction("Run", IE_Released, this, &AWIMPPlayerController::StopRun);
	InputComponent->BindAction("ChangeCamera", IE_Pressed, this, &AWIMPPlayerController::ChangeCamera);
}

void AWIMPPlayerController::ForwardMovement(float Value)
{
	const FRotator Rotation = GetControlRotation();
	const FRotator Yaw(0, Rotation.Yaw, 0);
	const FVector direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y);
	if (GetPawn())
		GetPawn()->AddMovementInput(direction, Value);
}

void AWIMPPlayerController::RightMovement(float Value)
{
	const FRotator Rotation = GetControlRotation();
	const FRotator Yaw(0, Rotation.Yaw, 0);
	const FVector direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);
	if (GetPawn())
		GetPawn()->AddMovementInput(direction, Value);
}

void AWIMPPlayerController::Jump()
{
	if (GetPawn()) {
		GetCharacter()->Jump();
		
	}
}

void AWIMPPlayerController::Run()
{
	if (GetPawn()) {
		GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 500.f;
	}
}

void AWIMPPlayerController::StopRun()
{
	if (GetPawn()) {
		GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 135.f;
	}
}

void AWIMPPlayerController::ChangeCamera()
{
	AWIMPCharacter* character = Cast<AWIMPCharacter>(GetPawn());
	if (character->IsValidLowLevel())
	{
		character->ChangeCamera();
	}
}
