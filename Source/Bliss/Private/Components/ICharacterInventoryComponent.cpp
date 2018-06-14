// Copyright 2018, Colby Hall. All Rights Reserved.

#include "ICharacterInventoryComponent.h"
#include "Items/IItem.h"
#include "Player/ICharacter.h"

bool UICharacterInventoryComponent::AddItem(class AIItem* Item)
{
	Super::AddItem(Item);

	if (!Item)
	{
		return false;
	}

	GetCharacterChecked()->Inventory.Add(Item);

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

