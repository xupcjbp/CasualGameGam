// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "CasualGameGamGameMode.h"

#include "CasualGameGamCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Util/Logging.h"

ACasualGameGamGameMode::ACasualGameGamGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ACasualGameGamGameMode::BeginPlay() {
	UE_LOG( CGJ, Display, TEXT( "My name is %s" ), TEXT( "Jeffrey" ) );
	UE_LOG( CGJ, Warning, TEXT( "My name is %s" ), TEXT( "Jeffrey" ) );
	UE_LOG( CGJ, Error, TEXT( "My name is %s" ), TEXT( "Jeffrey" ) );
}