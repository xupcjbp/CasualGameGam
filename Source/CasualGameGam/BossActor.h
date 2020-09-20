// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossActor.generated.h"

UCLASS()
class CASUALGAMEGAM_API ABossActor : public AActor
{
	GENERATED_BODY()


	FTimerHandle TimerHandle;

	
public:	
	// Sets default values for this actor's properties
	ABossActor();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UDamageTakingComponent* DamageTakingComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void DecideMove();

	void Move1();

	void Move2();

	void Move3();

	void Move4();

	void Move5();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
