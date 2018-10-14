// Copyright 2018, Colby Hall. All Rights Reserved.

#pragma once

#include "Bliss.h"
#include "IHUD.h"
#include "IPlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class BLISS_API AIPlayerHUD : public AIHUD
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	void OpenInventory();

	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	void CloseInventory();

protected:

	/**
	 * Only created when the player wants to open the inventory
	 *
	 * @protected
	 */
	UPROPERTY(EditDefaultsOnly, Category = HUD)
	TSubclassOf<UUserWidget> InventoryWidgetClass;

	/**
	 * Instance of inventory widget
	 *
	 * @see: InventoryWidgetClass
	 */
	UPROPERTY(Transient)
	UUserWidget* InventoryWidgetInstance;

	virtual void Destroyed() override;
	
};
