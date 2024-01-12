// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterAcecomGameMode.h"
#include "ShooterAcecomCharacter.h"
#include "UObject/ConstructorHelpers.h"

AShooterAcecomGameMode::AShooterAcecomGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
