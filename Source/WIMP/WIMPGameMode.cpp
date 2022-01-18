// Copyright Epic Games, Inc. All Rights Reserved.

#include "WIMPGameMode.h"
#include "WIMPPlayerController.h"
#include "WIMPCharacter.h"
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