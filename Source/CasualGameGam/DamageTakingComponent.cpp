// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageTakingComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/Engine.h"
#include "StatsObject.h"
#include "GameFramework/Character.h"

UDamageTakingComponent::UDamageTakingComponent()
{
	StatClass = UStatsObject::StaticClass();

	//If owner is type ACharacter disable capsule component overlap event and attach to capsule (root) component
	AActor* Owner = GetOwner();
	if (Cast<ACharacter>(Owner) != nullptr) {
		Cast<ACharacter>(Owner)->GetCapsuleComponent()->SetGenerateOverlapEvents(false);
		SetupAttachment(Cast<ACharacter>(Owner)->GetCapsuleComponent());
		SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	}

}

void UDamageTakingComponent::OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {


	UPrimitiveComponent* Weapon = OtherComp;
	float DamageTaken = GetDamageAmount(OtherActor, Weapon);
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, TEXT("Overlap begun with: ") + Weapon->GetName() + FString::Printf(TEXT("Damage taken = %f"), DamageTaken));
	
	
	Stats->DecreaseHealth(DamageTaken);
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, *FString::Printf(TEXT("Current Health:  %f"),Stats->GetCurrentHealth()));
}

void UDamageTakingComponent::OverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex) {
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, TEXT("Overlap ended: ") + OtherComp->GetName());


}

void UDamageTakingComponent::BeginPlay() {

	Super::BeginPlay();

	Stats = NewObject<UStatsObject> (
		this,
		StatClass.Get(),
		TEXT("StatsObject")
	);

	OnComponentBeginOverlap.AddDynamic(this, &UDamageTakingComponent::OverlapBegin);
	OnComponentEndOverlap.AddDynamic(this, &UDamageTakingComponent::OverlapEnd);


}

float UDamageTakingComponent::GetDamageAmount (AActor* Aggressor, UPrimitiveComponent* Weapon) {
	float AttackDamage = 0;
	float WeaponDamage = 0;
	if (Cast<ACharacter>(Aggressor) != nullptr && CheckActorDTC(Aggressor)!= nullptr) {
		AttackDamage = CheckActorDTC(Aggressor)->Stats->GetAttackDamage();
	}

	if (Weapon->GetName() == "BoxWeapon") {
		WeaponDamage =  1;
	}
	return AttackDamage + WeaponDamage;

}


UDamageTakingComponent* UDamageTakingComponent::CheckActorDTC(AActor* Actor) {
	UDamageTakingComponent* DTC = Cast<UDamageTakingComponent>(Actor->FindComponentByClass(UDamageTakingComponent::StaticClass()));
	return DTC;
}