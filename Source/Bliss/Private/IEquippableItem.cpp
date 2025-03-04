// Copyright 2018, Colby Hall. All Rights Reserved.

#include "IEquippableItem.h"
#include "Bliss.h"

FName AIEquippableItem::FirstPersonMeshComponentName(TEXT("First Person Mesh"));
FName AIEquippableItem::ThirdPersonMeshComponentName(TEXT("Third Person Mesh"));

AIEquippableItem::AIEquippableItem(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ThirdPersonMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, AIEquippableItem::ThirdPersonMeshComponentName);
	ThirdPersonMesh->SetupAttachment(RootComponent);
	ThirdPersonMesh->bOwnerNoSee = true;
	ThirdPersonMesh->bCastHiddenShadow = true;

	FirstPersonMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, AIEquippableItem::FirstPersonMeshComponentName);
	FirstPersonMesh->SetupAttachment(RootComponent);
	FirstPersonMesh->bOnlyOwnerSee = true;
	FirstPersonMesh->CastShadow = false;

	Description.ItemType = EItemType::Equippable;
	SocketName = NAME_None;
}

void AIEquippableItem::Equip_Implementation()
{
	// We should already have the owner by now and it should be a character
	AICharacter* OwningCharacter = GetCharacterChecked();
	SetActorHiddenInGame(false);

	ThirdPersonMesh->AttachToComponent(OwningCharacter->GetThirdPersonMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
	FirstPersonMesh->AttachToComponent(OwningCharacter->GetFirstPersonMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);

}

void AIEquippableItem::UnEquip_Implementation()
{

}

void AIEquippableItem::StartFiring_Implementation()
{

}

void AIEquippableItem::StopFiring_Implementation()
{

}

void AIEquippableItem::StartAiming_Implementation()
{

}

void AIEquippableItem::StopAiming_Implementation()
{

}

void AIEquippableItem::SetCameraView(const ECameraView NewCameraView)
{
	Super::SetCameraView(NewCameraView);
	const bool bFirstPerson = NewCameraView == ECameraView::FirstPerson;

	GetFirstPersonMesh()->SetOwnerNoSee(!bFirstPerson);
	GetThirdPersonMesh()->SetOwnerNoSee(bFirstPerson);
}

ECameraView AIEquippableItem::GetCameraView() const
{
	AICharacter* OwningCharacter = GetCharacter();
	if (OwningCharacter)
	{
		return OwningCharacter->GetCameraView();
	}

	return ECameraView::ThirdPerson;
}

