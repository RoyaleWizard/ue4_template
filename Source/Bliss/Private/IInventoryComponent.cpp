// Copyright 2018, Colby Hall. All Rights Reserved.

#include "IInventoryComponent.h"
#include "IItem.h"


bool UIInventoryComponent::AddItem(AIItem* Item)
{
	// Only call this on the server
	ensure(GetOwnerRole() == ROLE_Authority);

	return false;
}

bool UIInventoryComponent::RemoveItem(AIItem* Item)
{
	// Only call this on the server
	ensure(GetOwnerRole() == ROLE_Authority);

	return false;
}