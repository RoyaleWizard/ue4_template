// Copyright 2018, Colby Hall. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/IInventoryComponent.h"
#include "ICharacterInventoryComponent.generated.h"

/**
 * 
 */
UCLASS()
class BLISS_API UICharacterInventoryComponent : public UIInventoryComponent
{
	GENERATED_BODY()
	
public:

	virtual bool AddItem(class AIItem* Item) override;
	virtual bool RemoveItem(class AIItem* Item) override;

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
	
	
};
