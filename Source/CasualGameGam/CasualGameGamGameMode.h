// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CasualGameGamGameMode.generated.h"

UCLASS(minimalapi)
class ACasualGameGamGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACasualGameGamGameMode();

protected:
	virtual void BeginPlay() override;
};



