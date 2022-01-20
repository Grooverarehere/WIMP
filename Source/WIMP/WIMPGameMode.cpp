// Copyright Epic Games, Inc. All Rights Reserved.

#include "WIMPGameMode.h"
#include "WIMPPlayerController.h"
#include "WIMPCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AWIMPGameMode::AWIMPGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AWIMPPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_Marian"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AWIMPGameMode::BeginPlay()
{
	Super::BeginPlay();
	BindRespawn();
}

void AWIMPGameMode::Respawn(AActor* actor)
{
	AWIMPPlayerController* controller = Cast<AWIMPPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if(controller->IsValidLowLevel())
	{
		RestartPlayerAtPlayerStart(controller, FindPlayerStart(controller));
		BindRespawn();
	}
	
}

void AWIMPGameMode::BindRespawn()
{
	AWIMPCharacter* character = Cast<AWIMPCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (character)
	{
		character->OnDestroyed.AddDynamic(this, &AWIMPGameMode::Respawn);
	}
}
