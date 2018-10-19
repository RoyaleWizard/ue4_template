// Copyright 2018, Colby Hall. All Rights Reserved.

#include "IWearableItem.h"
#include "Bliss.h"


void FWearableInventoryItem::PostReplicatedAdd(const struct FWearableInventoryArray& InArraySerializer)
{
	Item->SetOwner(InArraySerializer.Owner);
	Item->OnPickedUp();
}

void FWearableInventoryArray::Add(AIItem* Item)
{
	ensure(Owner->HasAuthority());

	FWearableInventoryItem InventoryItem;
	InventoryItem.Item = Item;
	Array.Add(InventoryItem);
	MarkItemDirty(InventoryItem);
}

bool FWearableInventoryArray::Remove(AIItem* Item)
{
	ensure(Owner->HasAuthority());

	for (int32 i = 0; i < Array.Num(); i++)
	{
		if (Array[i].Item == Item)
		{
			Array.RemoveAt(i);
			return true;
		}
	}

	return false;
}

bool FWearableInventoryArray::Contains(const AIItem* Item)
{
	for (auto ItemData : Array)
	{
		if (ItemData.Item == Item)
		{
			return true;
		}
	}
	return false;
}

TArray<AIItem*> FWearableInventoryArray::GetArrayAsItems() const
{
	TArray<AIItem*> Result;
	Result.Reserve(Array.Num());

	for (auto It : Array)
	{
		Result.Add(It.Item);
	}

	return Result;
}

FName AIWearableItem::FirstPersonMeshComponentName(TEXT("First Person Mesh"));
FName AIWearableItem::ThirdPersonMeshComponentName(TEXT("Third Person Mesh"));

AIWearableItem::AIWearableItem(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ThirdPersonMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, AIWearableItem::ThirdPersonMeshComponentName);
	ThirdPersonMesh->SetupAttachment(RootComponent);
	ThirdPersonMesh->bOwnerNoSee = true;
	ThirdPersonMesh->bCastHiddenShadow = true;

	FirstPersonMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, AIWearableItem::FirstPersonMeshComponentName);
	FirstPersonMesh->SetupAttachment(RootComponent);
	FirstPersonMesh->bOnlyOwnerSee = true;
	FirstPersonMesh->CastShadow = false;

	Description.ItemType = EItemType::Equippable;
}

void AIWearableItem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AIWearableItem, Inventory);
}

TArray<AIItem*> AIWearableItem::GetInventoryArray() const
{
	return Inventory.GetArrayAsItems();
}

void AIWearableItem::AddItem(AIItem* Item)
{
	ServerAddItem(Item);
}

void AIWearableItem::RemoveItem(AIItem* Item)
{
	ServerAddItem(Item);
}

float AIWearableItem::GetCurrentWeight() const
{
	TArray<AIItem*> Inventory = GetInventoryArray();
	float Result = 0.f;
	for (AIItem* Item : Inventory)
	{
		if (Item)
		{
			const float ItemWeight = Item->GetItemDescription().Weight;
			Result += ItemWeight;
		}
	}

	return Result;
}

bool AIWearableItem::CanAddItem(const AIItem* Item) const
{
	if (Item)
	{
		const float ItemWeight = Item->GetItemDescription().Weight;
		const float CurrentWeight = GetCurrentWeight();

		if (ItemWeight + CurrentWeight <= WeightCapacity)
		{
			return true;
		}
	}

	return false;
}

void AIWearableItem::ServerAddItem_Implementation(AIItem* Item)
{
	Inventory.Add(Item);
}

bool AIWearableItem::ServerAddItem_Validate(AIItem* Item)
{
	return true;
}

void AIWearableItem::ServerRemoveItem_Implementation(AIItem* Item)
{
	Inventory.Remove(Item);
}

bool AIWearableItem::ServerRemoveItem_Validate(AIItem* Item)
{
	return true;
}
