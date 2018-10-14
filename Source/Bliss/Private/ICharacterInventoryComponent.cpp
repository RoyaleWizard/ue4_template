// Copyright 2018, Colby Hall. All Rights Reserved.

#include "ICharacterInventoryComponent.h"
#include "IItem.h"
#include "IEquippableItem.h"
#include "ICharacter.h"

bool UICharacterInventoryComponent::AddItem(AIItem* Item)
{
	Super::AddItem(Item);

	if (!Item) return false;

	Item->SetOwner(GetCharacterChecked());
	GetCharacterChecked()->Inventory.Add(Item);
	Item->OnPickedUp();

	if (Item->IsA<AIEquippableItem>())
	{
		GetCharacterChecked()->EquipItem(Cast<AIEquippableItem>(Item));
	}

	return true;
}

bool UICharacterInventoryComponent::RemoveItem(AIItem* Item)
{
	Super::RemoveItem(Item);

	if (!Item) return false;

	GetCharacterChecked()->Inventory.Remove(Item);
	Item->OnDropped();

	return true;
}


AICharacter* UICharacterInventoryComponent::GetCharacter() const
{
	return Cast<AICharacter>(GetOwner());
}

AICharacter* UICharacterInventoryComponent::GetCharacterChecked() const
{
	AICharacter* Result = Cast<AICharacter>(GetOwner());
	check(Result != nullptr);
	return Result;
}

