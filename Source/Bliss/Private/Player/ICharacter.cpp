// Copyright 2018, Colby Hall. All Rights Reserved.

#include "ICharacter.h"
#include "Bliss.h"

FName AICharacter::FirstPersonMeshName(TEXT("First Person Mesh"));
FName AICharacter::FirstPersonCameraName(TEXT("First Person Camera"));
FName AICharacter::ThirdPersonArmName(TEXT("Third Person Arm"));
FName AICharacter::ThirdPersonCameraName(TEXT("Third Person Camera"));

AICharacter::AICharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	FirstPersonMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, AICharacter::FirstPersonMeshName);
	FirstPersonMesh->bOnlyOwnerSee = true;
	FirstPersonMesh->CastShadow = false;
	FirstPersonMesh->SetupAttachment(GetMesh());

	GetMesh()->bOwnerNoSee = true;
	GetMesh()->bCastHiddenShadow = true;

	FirstPersonCamera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, AICharacter::FirstPersonCameraName);
	FirstPersonCamera->SetupAttachment(GetFirstPersonMesh(), CAMERA_SOCKET);
	FirstPersonCamera->bUsePawnControlRotation = false;

	ThirdPersonArm = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, AICharacter::ThirdPersonArmName);
	ThirdPersonArm->SetupAttachment(GetMesh(), TP_ARM_SOCKET);
	ThirdPersonArm->bUsePawnControlRotation = true;

	ThirdPersonCamera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, AICharacter::ThirdPersonCameraName);
	ThirdPersonCamera->SetupAttachment(GetThirdPersonArm(), USpringArmComponent::SocketName);

	bUseControllerRotationYaw = true;

}

void AICharacter::BeginPlay()
{
	Super::BeginPlay();

	// @TODO: Store last saved camera view and use that one on play
	if (Role != ROLE_Authority)
	{
		SetCameraView(ECameraView::ThirdPerson);
	}

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

	PlayerInputComponent->BindAction("SwitchCamera", IE_Pressed, this, &AICharacter::SwitchCamera);

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

USkeletalMeshComponent* AICharacter::GetFirstPersonMesh() const
{
	return FirstPersonMesh;
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

ECameraView AICharacter::GetCameraView() const
{
	if (GetFirstPersonCamera()->IsActive())
	{
		return ECameraView::FirstPerson;
	}

	return ECameraView::ThirdPerson;
}

void AICharacter::SetCameraView(const ECameraView NewCameraView)
{
	if (NewCameraView == ECameraView::FirstPerson)
	{
		GetFirstPersonCamera()->Activate();
		GetFirstPersonMesh()->SetHiddenInGame(false);
		GetThirdPersonCamera()->Deactivate();
		GetMesh()->SetOwnerNoSee(true);
	}
	else
	{
		GetFirstPersonCamera()->Deactivate();
		GetFirstPersonMesh()->SetHiddenInGame(true);
		GetThirdPersonCamera()->Activate();
		GetMesh()->SetOwnerNoSee(false);
	}
}

void AICharacter::SwitchCamera()
{
	const ECameraView CurrentView = GetCameraView();

	if (CurrentView == ECameraView::FirstPerson)
	{
		SetCameraView(ECameraView::ThirdPerson);
	}
	else
	{
		SetCameraView(ECameraView::FirstPerson);
	}
}

