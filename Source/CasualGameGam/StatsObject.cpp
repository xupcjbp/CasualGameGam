// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsObject.h"

UStatsObject::UStatsObject()
{

	InitialHealth = 100;

	CurrentHealth = InitialHealth;

	AttackDamage = 10;

}

float UStatsObject::GetCurrentHealth() {
	return CurrentHealth;
}

float UStatsObject::GetAttackDamage() {
	return AttackDamage;
}

void UStatsObject::ResetHealth() {
	CurrentHealth = InitialHealth;
}

void UStatsObject::DecreaseHealth(float amount) {
	if (CurrentHealth - amount <= 0) {
		CurrentHealth = 0;
	}
	else {
		CurrentHealth = CurrentHealth - amount;
	}
	
}

void UStatsObject::IncreaseHealth(float amount) {
	CurrentHealth = CurrentHealth + amount;
}