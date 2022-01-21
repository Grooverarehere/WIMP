// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WIMPPlayerController.generated.h"

UCLASS()
class AWIMPPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AWIMPPlayerController();
	float m_WalkSpeed;
	float m_RunSpeed;
protected:
	virtual void BeginPlay() override;
	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	void ForwardMovement(float Value);
	void RightMovement(float Value);
	void Jump();
	void Run();
	void StopRun();
private:
	
};


