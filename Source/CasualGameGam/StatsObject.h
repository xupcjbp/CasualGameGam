// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StatsObject.generated.h"

/**
 * 
 */
UCLASS( Blueprintable, notplaceable )
class CASUALGAMEGAM_API UStatsObject : public UObject
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStatsObject();


	float GetCurrentHealth();

	float GetAttackDamage();

	void DecreaseHealth(float amount);

	void IncreaseHealth(float amount);

	void ResetHealth();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float InitialHealth;

protected:

	/** Current Health */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float CurrentHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float AttackDamage;
};
