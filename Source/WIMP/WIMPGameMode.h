// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WIMPGameMode.generated.h"

UCLASS(minimalapi)
class AWIMPGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AWIMPGameMode();

private:
	FVector InitPosition;
	FRotator InitRotation;

	virtual void BeginPlay() override;
	UFUNCTION()
		void Respawn(AActor* actor);
	void BindRespawn();
};



