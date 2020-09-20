// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "CasualGameGamCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/Engine.h"
#include "DamageTakingComponent.h"
#include "StatsObject.h"

//////////////////////////////////////////////////////////////////////////
// ACasualGameGamCharacter

ACasualGameGamCharacter::ACasualGameGamCharacter()
{
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false; 

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

	// Create DTC component
	DamageTakingComponent = CreateDefaultSubobject<UDamageTakingComponent>(TEXT("DamageTakingComponent"));
	
	//RootComponent = DamageTakingComponent;
	

	/*GetCharacterMovement()->UpdatedComponent = DamageTakingComponent;
	DamageTakingComponent->CanCharacterStepUpOn = ECB_No;
	DamageTakingComponent->SetShouldUpdatePhysicsVolume(true);
	DamageTakingComponent->SetCanEverAffectNavigation(false);
	DamageTakingComponent->bDynamicObstacle = true;
	DamageTakingComponent->SetCanEverAffectNavigation(bCanAffectNavigationGeneration);*/
	


	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

UStatsObject* ACasualGameGamCharacter::GetStats() {
	return DamageTakingComponent->Stats;
}

//////////////////////////////////////////////////////////////////////////
// Input

void ACasualGameGamCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ACasualGameGamCharacter::NewCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ACasualGameGamCharacter::NewUnCrouch);


	PlayerInputComponent->BindAxis("MoveForward", this, &ACasualGameGamCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACasualGameGamCharacter::MoveRight);

	

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ACasualGameGamCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ACasualGameGamCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ACasualGameGamCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ACasualGameGamCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ACasualGameGamCharacter::OnResetVR);
}



// Called when the game starts or when spawned
void ACasualGameGamCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->UpdateNavAgent(*DamageTakingComponent);

}


void ACasualGameGamCharacter::NewCrouch() {
	Crouch();
}

void ACasualGameGamCharacter::NewUnCrouch() {
	UnCrouch();
}

void ACasualGameGamCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ACasualGameGamCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ACasualGameGamCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void ACasualGameGamCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ACasualGameGamCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ACasualGameGamCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ACasualGameGamCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
