// Copyright 2018, Colby Hall. All Rights Reserved.

#include "IHumanCharacter.h"

FName AIHumanCharacter::ThirdPersonHeadMeshComponentName(TEXT("Third Person Head Mesh"));

AIHumanCharacter::AIHumanCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ThirdPersonHeadMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, AIHumanCharacter::ThirdPersonHeadMeshComponentName);
	ThirdPersonHeadMesh->SetupAttachment(GetThirdPersonMesh());
	ThirdPersonHeadMesh->SetMasterPoseComponent(GetThirdPersonMesh());
}

void AIHumanCharacter::SetCameraView(const ECameraView NewCameraView)
{
	Super::SetCameraView(NewCameraView);
	const bool bFirstPerson = NewCameraView == ECameraView::FirstPerson;

	GetThirdPersonHeadMesh()->SetOwnerNoSee(bFirstPerson);
	GetThirdPersonHeadMesh()->bCastHiddenShadow = bFirstPerson;
}

