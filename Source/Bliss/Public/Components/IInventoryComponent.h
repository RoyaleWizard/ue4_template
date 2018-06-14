// Copyright 2018, Colby Hall. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IInventoryComponent.generated.h"


/**
 * Base Inventory Component Class
 * 
 * Not replicated. Just used to manage Inventory
 */
UCLASS(ClassGroup=(Custom), Abstract)
class BLISS_API UIInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	/**
	 * Adds item to an Inventory
	 *
	 * @role: AuthorityOnly
	 * @param: Item is the item to be added
	 * @returns: bool if added or not
	 */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	virtual bool AddItem(class AIItem* Item);

	/**
	* Removes item from an Inventory
	*
	* @role: AuthorityOnly
	* @param: Item is the item to be removed
	* @returns: bool if removed or not
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	virtual bool RemoveItem(class AIItem* Item);
	


};
