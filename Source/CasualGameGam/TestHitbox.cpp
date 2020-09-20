// Fill out your copyright notice in the Description page of Project Settings.


#include "TestHitbox.h"
#include "Components/BoxComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/Engine.h"
#include "CasualGameGamCharacter.h"
#include "DamageTakingComponent.h"
#include "StatsObject.h"

// Sets default values
ATestHitbox::ATestHitbox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxWeapon"));
	BoxComponent->bHiddenInGame = false;
	RootComponent = BoxComponent;
}



// Called when the game starts or when spawned
void ATestHitbox::BeginPlay()
{

	Super::BeginPlay();

}

// Called every frame
void ATestHitbox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

