// Copyright 2018, Colby Hall. All Rights Reserved.

#include "IItem.h"

AIItem::AIItem(const FObjectInitializer& ObjectInitializer)
{
	bReplicates = true;
	bNetUseOwnerRelevancy = true;
	NetUpdateFrequency = 10.f;
}

bool AIItem::IsInInventory() const
{
	return false;
}

AICharacter* AIItem::GetCharacter() const
{
	return Cast<AICharacter>(GetOwner());
}

AICharacter* AIItem::GetCharacterChecked() const
{
	AICharacter* Result = Cast<AICharacter>(GetOwner());
	check(Result != nullptr);
	return Result;
}

void AIItem::Pickup(AActor* EventInstigator)
{
	AICharacter* OwningCharacter = Cast<AICharacter>(EventInstigator);
	if (OwningCharacter)
	{
		OwningCharacter->PickupItem(this);
	}
}

void AIItem::OnPickedUp_Implementation()
{
	Store();
}

void AIItem::OnDropped_Implementation()
{

}

void AIItem::Store_Implementation()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
}

void AIItem::GetInteractionOptions_Implementation(AActor* EventInstigator, TArray<FInteractionOption>& OutInteractions)
{
	FInteractionOption Out;
	Out.DisplayText = NSLOCTEXT("Interaction", "Pickup", "Pickup");
	Out.FunctionName = "Pickup";
	Out.Object = this;

	OutInteractions.Add(Out);
}

void AIItem::SetCameraView(const ECameraView NewCameraView)
{

}
