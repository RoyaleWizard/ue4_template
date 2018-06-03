// Copyright 2018, Colby Hall. All Rights Reserved.

#include "ICharacter.h"
#include "Bliss.h"


AICharacter::AICharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	FirstPersonCamera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, "First Person Camera");
	FirstPersonCamera->SetupAttachment(GetMesh(), CAMERA_SOCKET);
	FirstPersonCamera->bUsePawnControlRotation = false;

	ThirdPersonArm = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, "Third Person Arm");
	ThirdPersonArm->SetupAttachment(GetMesh(), CAMERA_SOCKET);
	ThirdPersonArm->bUsePawnControlRotation = false;

	ThirdPersonCamera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, "Third Person Camera");
	ThirdPersonCamera->SetupAttachment(GetThirdPersonArm(), USpringArmComponent::SocketName);

	bUseControllerRotationYaw = true;

}

void AICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

float AICharacter::GetInputScale() const
{
	return 1.f;
}

void AICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AICharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AICharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AICharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AICharacter::LookUp);

}

void AICharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void AICharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void AICharacter::Turn(float Value)
{
	AddControllerYawInput(Value * GetInputScale());
}

void AICharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value * GetInputScale());
}

UCameraComponent* AICharacter::GetFirstPersonCamera() const
{
	return FirstPersonCamera;
}

USpringArmComponent* AICharacter::GetThirdPersonArm() const
{
	return ThirdPersonArm;
}

UCameraComponent* AICharacter::GetThirdPersonCamera() const
{
	return ThirdPersonCamera;
}

