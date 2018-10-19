// Copyright 2018, Colby Hall. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IItem.h"
#include "IWearableItem.generated.h"

class AIWearableItem;

/**
* Data struct that can be serialized
*
* @see FWearableInventoryArray
*/
USTRUCT()
struct FWearableInventoryItem : public FFastArraySerializerItem
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	AIItem* Item;

	void PostReplicatedAdd(const struct FWearableInventoryArray& InArraySerializer);
};

/**
* Special array that all InventoryItems
*
* @see FWearableInventoryItem
*/
USTRUCT()
struct FWearableInventoryArray : public FFastArraySerializer
{
	GENERATED_USTRUCT_BODY()

private:
	/**
	* Actual array used for holding the data
	*
	* @private because we don't want anyone removing items from this
	*/
	UPROPERTY()
	TArray<FWearableInventoryItem> Array;

public:

	/**
	* This is used so we can get a reference to the world
	*
	* @see FWearableInventoryItem::PostReplicatedAdd
	*/
	UPROPERTY(NotReplicated)
	AIWearableItem* Owner;

	void Add(AIItem* Item);
	bool Remove(AIItem* Item);
	bool Contains(const AIItem* Item);
	TArray<AIItem*> GetArrayAsItems() const;

	bool NetDeltaSerialize(FNetDeltaSerializeInfo & DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FWearableInventoryItem, FWearableInventoryArray>(Array, DeltaParms, *this);
	}
};

template<>
struct TStructOpsTypeTraits<FWearableInventoryArray> : public TStructOpsTypeTraitsBase2<FWearableInventoryArray>
{
	enum
	{
		WithNetDeltaSerializer = true,
	};
};


/**
 * 
 */
UCLASS()
class BLISS_API AIWearableItem : public AIItem
{
	GENERATED_BODY()
	
public:

	AIWearableItem(const FObjectInitializer& ObjectInitializer);

private:

	/** First Person Equippable Mesh*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* FirstPersonMesh;

	/** Third Person Equippable Mesh*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* ThirdPersonMesh;

public:

	FORCEINLINE class USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMesh; }

	/** Name of the First Person Mesh*/
	static FName FirstPersonMeshComponentName;

	FORCEINLINE class USkeletalMeshComponent* GetThirdPersonMesh() const { return ThirdPersonMesh; }

	/** Name of the Third Person Mesh*/
	static FName ThirdPersonMeshComponentName;

protected:

	/**
	* Total weight this item can hold
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Item, Meta = (ClampMin = "0", UIMin = "0"))
	float WeightCapacity;

public:

	/**
	* Inventory Fast Array
	*
	* @public for easier access
	*/
	UPROPERTY(Replicated, Transient)
	FWearableInventoryArray Inventory;

	UFUNCTION(BlueprintCallable, Meta = (DisplayName = "Get Inventory"))
	TArray<AIItem*> GetInventoryArray() const;

	/**
	 * Adds item to the inventory array
	 *
	 * @see IWearableItem.h
	 */
	UFUNCTION(BlueprintCallable)
	void AddItem(AIItem* Item);

	/**
	 * Removes item from the inventory array
	 *
	 * @see IWearableItem.h
	 */
	UFUNCTION(BlueprintCallable)
	void RemoveItem(AIItem* Item);

	UFUNCTION(BlueprintCallable)
	float GetCurrentWeight() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool CanAddItem(const AIItem* Item) const;

	FORCEINLINE float GetWeightCapacity() const { return WeightCapacity; }

private:

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerAddItem(AIItem* Item);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRemoveItem(AIItem* Item);
	
	
};
