// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsComponent.h"

// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	InitialHealth = 100;

	CurrentHealth = InitialHealth;

	AttackDamage = 10;
}


// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

float UStatsComponent::GetCurrentHealth() {
	return CurrentHealth;
}

float UStatsComponent::GetAttackDamage() {
	return AttackDamage;
}

void UStatsComponent::ResetHealth() {
	CurrentHealth = InitialHealth;
}

void UStatsComponent::DecreaseHealth(float amount) {
	CurrentHealth = CurrentHealth - amount;
}

void UStatsComponent::IncreaseHealth(float amount) {
	CurrentHealth = CurrentHealth + amount;
}


// Called every frame
void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

