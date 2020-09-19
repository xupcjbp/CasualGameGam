// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASUALGAMEGAM_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatsComponent();
	

	float GetCurrentHealth();

	float GetAttackDamage();

	void DecreaseHealth(float amount);

	void IncreaseHealth(float amount);

	void ResetHealth();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InitialHealth;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/** Current Health */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float CurrentHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float AttackDamage;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
