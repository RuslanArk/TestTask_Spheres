// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestTaskGameMode.h"
#include "TestTaskHUD.h"
#include "TestTaskCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATestTaskGameMode::ATestTaskGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATestTaskHUD::StaticClass();
}
