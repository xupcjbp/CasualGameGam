// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

class UAnimMontage;
class USkeletalMeshComponent;

#include "BossActor.generated.h"

UCLASS()
class CASUALGAMEGAM_API ABossActor : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent *BossComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UDamageTakingComponent* DamageTakingComponent;

	UPROPERTY(EditAnywhere)
	UAnimMontage *PlateAtkAnimMontage;

	UPROPERTY(EditAnywhere)
	UAnimMontage *CubePushAtkAnimMontage;
	UPROPERTY(EditAnywhere)
	UAnimMontage *CubeSwingAtkAnimMontage;

	UPROPERTY(EditAnywhere)
	UAnimMontage *Sphere1AtkAnimMontage;
	UPROPERTY(EditAnywhere)
	UAnimMontage *Sphere2AtkAnimMontage;
	UPROPERTY(EditAnywhere)
	UAnimMontage *Sphere3AtkAnimMontage;
	UPROPERTY(EditAnywhere)
	UAnimMontage *Sphere4AtkAnimMontage;

	ABossActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void DecideMove();

	void Move1();

	void Move2();

	void Move3();

	void Move4();

	void Move5();

	void PerforMove( UAnimMontage *montage );


private:
	FTimerHandle TimerHandle;
};
