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

protected:
	
	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	void ForwardMovement(float Value);
	void RightMovement(float Value);
	void Jump();
	void Run();
	void StopRun();
};


