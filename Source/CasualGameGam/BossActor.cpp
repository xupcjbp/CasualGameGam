// Fill out your copyright notice in the Description page of Project Settings.


#include "BossActor.h"
#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "DamageTakingComponent.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "StatsObject.h"
#include "TimerManager.h"

// Sets default values
ABossActor::ABossActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	TimerHandle = FTimerHandle();

	PrimaryActorTick.bCanEverTick = true;
	
	DamageTakingComponent = CreateDefaultSubobject<UDamageTakingComponent>(TEXT("DamageTakingComponent"));
	RootComponent = DamageTakingComponent;

	BossComponent = CreateDefaultSubobject<USkeletalMeshComponent>( TEXT( "BossComponent" ) );
	BossComponent->SetupAttachment( RootComponent );
}

// Called when the game starts or when spawned
void ABossActor::BeginPlay()
{
	Super::BeginPlay();

	//Set timer for DecideMove
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABossActor::DecideMove, 4, true);
}

// Called every frame
void ABossActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Decides what move to use and then calls the move function
void ABossActor::DecideMove() {
	if (DamageTakingComponent->Stats->GetCurrentHealth() == 0) {
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

	PerforMove( PlateAtkAnimMontage );
}

void ABossActor::Move2() {
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, TEXT("Move 2 Activated"));

	PerforMove( CubePushAtkAnimMontage );
}

void ABossActor::Move3() {
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, TEXT("Move 3 Activated"));

	PerforMove( CubeSwingAtkAnimMontage );
}

void ABossActor::Move4() {
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, TEXT("Move 4 Activated"));

	PerforMove( Sphere1AtkAnimMontage );
	PerforMove( Sphere3AtkAnimMontage );
}

void ABossActor::Move5() {
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, TEXT("Move 5 Activated"));

	PerforMove( Sphere2AtkAnimMontage );
	PerforMove( Sphere4AtkAnimMontage );
}

void ABossActor::PerforMove( UAnimMontage *montage ) {
	UAnimInstance *AnimInstance = (BossComponent)? BossComponent->GetAnimInstance() : nullptr;
	if( AnimInstance && montage ) {
		AnimInstance->Montage_Play( montage, 1.f, EMontagePlayReturnType::Duration, 0.f, false );
	}
}