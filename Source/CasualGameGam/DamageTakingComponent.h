// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "StatsObject.h"
#include "DamageTakingComponent.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
class CASUALGAMEGAM_API UDamageTakingComponent : public UCapsuleComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDamageTakingComponent();

	UPROPERTY(EditAnywhere)
	TSubclassOf<UStatsObject> StatClass;

	UPROPERTY()
	UStatsObject* Stats;

	UFUNCTION()
		void OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
