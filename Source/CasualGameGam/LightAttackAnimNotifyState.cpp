// Fill out your copyright notice in the Description page of Project Settings.


#include "LightAttackAnimNotifyState.h"
#include "Engine/Engine.h"



void ULightAttackAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Yellow, __FUNCTION__);
}
void ULightAttackAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Yellow, __FUNCTION__);
}
void ULightAttackAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Yellow, __FUNCTION__);
}