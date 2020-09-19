// Fill out your copyright notice in the Description page of Project Settings.


#include "TestHitbox.h"
#include "Components/BoxComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/Engine.h"
#include "CasualGameGamCharacter.h"
#include "StatsComponent.h"

// Sets default values
ATestHitbox::ATestHitbox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->bHiddenInGame = false;

}

void ATestHitbox::OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, TEXT("Overlap begun: ") + OtherActor->GetName());
	ACasualGameGamCharacter* Character = Cast<ACasualGameGamCharacter>(OtherActor);
	
	UStatsComponent* CharStatsComponent = Character->GetStats();
	CharStatsComponent->DecreaseHealth(10);
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, *FString::Printf(TEXT("Overlap:  %f"), CharStatsComponent->GetCurrentHealth()));
}

void ATestHitbox::OverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex) {
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, TEXT("Overlap ended: ") + OtherActor->GetName());
	

}


// Called when the game starts or when spawned
void ATestHitbox::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ATestHitbox::OverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ATestHitbox::OverlapEnd);

}

// Called every frame
void ATestHitbox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

