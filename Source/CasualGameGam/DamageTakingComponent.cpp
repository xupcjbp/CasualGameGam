// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageTakingComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/Engine.h"
#include "StatsObject.h"
#include "GameFramework/Character.h"

UDamageTakingComponent::UDamageTakingComponent()
{
	Stats = NewObject<UStatsObject> (
		this,
		UStatsObject::StaticClass(),
		TEXT("StatsObject")
		);

	//If owner is type ACharacter disable capsule component overlap event
	AActor* Owner = GetOwner();
	if (Cast<ACharacter>(Owner) != nullptr) {
		Cast<ACharacter>(Owner)->GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	}

}

void UDamageTakingComponent::OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {


	UPrimitiveComponent* Weapon = OtherComp;
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, TEXT("Overlap begun with: ") + Weapon->GetName());
	
	
	Stats->DecreaseHealth(10);
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, *FString::Printf(TEXT("Current Health:  %f"),Stats->GetCurrentHealth()));
}

void UDamageTakingComponent::OverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex) {
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, TEXT("Overlap ended: ") + OtherComp->GetName());


}

void UDamageTakingComponent::BeginPlay() {

	Super::BeginPlay();

	
	OnComponentBeginOverlap.AddDynamic(this, &UDamageTakingComponent::OverlapBegin);
	OnComponentEndOverlap.AddDynamic(this, &UDamageTakingComponent::OverlapEnd);

	


}