// Fill out your copyright notice in the Description page of Project Settings.


#include "BossActor.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "StatsComponent.h"

// Sets default values
ABossActor::ABossActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	FTimerHandle TimerHandle;

	PrimaryActorTick.bCanEverTick = true;
	StatsComponent = CreateDefaultSubobject<UStatsComponent>(TEXT("StatsComponent"));
	
}

// Called when the game starts or when spawned
void ABossActor::BeginPlay()
{
	Super::BeginPlay();

	//Set timer for DecideMove
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABossActor::DecideMove, 5, true);
	
}

// Called every frame
void ABossActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Decides what move to use and then calls the move function
void ABossActor::DecideMove() {
	if (StatsComponent->GetCurrentHealth() == 0) {
		//Don't decide move and stop timer
	}

	int MoveNum = rand() % 5 + 1;
	switch (MoveNum) {
	case 1:
		Move1();
		break;
	
	case 2:
		Move2();
		break;

	case 3:
		Move3();
		break;

	case 4:
		Move4();
		break;

	case 5:
		Move5();
		break;
	}
}

void ABossActor::Move1() {
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, TEXT("Move 1 Activated"));
}

void ABossActor::Move2() {
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, TEXT("Move 2 Activated"));
}

void ABossActor::Move3() {
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, TEXT("Move 3 Activated"));
}

void ABossActor::Move4() {
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, TEXT("Move 4 Activated"));
}

void ABossActor::Move5() {
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, TEXT("Move 5 Activated"));
}

