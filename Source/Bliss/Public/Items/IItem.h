// Copyright 2018, Colby Hall. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IInteractionInterface.h"
#include "IItem.generated.h"


UENUM(BlueprintType)
enum class EItemType : uint8
{
	Generic,
	Consumable,
	Stackable,
	Equippable,
	Wearable,
	Firearm,
	Max
};

USTRUCT(BlueprintType)
struct FItemDescription
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TAssetPtr<UTexture2D> Icon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EItemType ItemType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Weight;

};

/**
 * Base item class for all inventory items
 *
 * @abstract
 */
UCLASS(Abstract, HideCategories=("Actor Tick", Input, Actor, LOD, Cooking))
class BLISS_API AIItem : public AActor, public IIInteractionInterface
{
	GENERATED_BODY()
	
public:	
	AIItem(const FObjectInitializer& ObjectInitializer);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Item)
	FItemDescription Description;

public:

	/** Returns true if the Item is in a Inventory */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Inventory)
	virtual bool IsInInventory() const;	

	/** Gets a copy of the item description*/
	FORCEINLINE FItemDescription GetItemDescription() const { return Description; }

	/**
	* Gets owner casted to AICharacter
	*
	* @returns CastedCharacter
	* @see GetOwner()
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
	class AICharacter* GetCharacter() const;

	/**
	* Gets owner casted to AICharacter but it is checked
	*
	* @returns CastedCharacter
	* @see GetOwner()
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
	class AICharacter* GetCharacterChecked() const;

public:

	UFUNCTION()
	void Pickup(AActor* EventInstigator);

	/**
	 * Event called when this item is picked up
	 */
	UFUNCTION(BlueprintNativeEvent)
	void OnPickedUp();

	/**
	* Event called when this item is dropped
	*/
	UFUNCTION(BlueprintNativeEvent)
	void OnDropped();

	/**
	 * Store this item in whatever owner is owning it
	 */
	UFUNCTION(BlueprintNativeEvent)
	void Store();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void GetInteractionOptions(AActor* EventInstigator, TArray<FInteractionOption>& OutInteractions);
	
};
