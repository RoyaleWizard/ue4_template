// Copyright 2018, Colby Hall. All Rights Reserved.

#pragma once

#include "Bliss.h"
#include "IHUD.h"
#include "IPlayerHUD.generated.h"

class UILobbyMap;

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
	
	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	void ToggleMap();

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

	/**
	 * Only created when the player wants to open the map
	 *
	 * @protected
	 */
	UPROPERTY(EditDefaultsOnly, Category = HUD)
	TSubclassOf<UILobbyMap> MapWidgetClass;

	/**
	 * Instance of inventory widget
	 *
	 * @see: InventoryWidgetClass
	 */
	


	virtual void Destroyed() override;
	//virtual void PostInitializeComponents() override; // All game elements are created, add the lobby menu
	//virtual void DrawHUD() override; // The HUD is drawn on our screen

public:
	UPROPERTY()
	UILobbyMap* MapWidgetInstance;
};
