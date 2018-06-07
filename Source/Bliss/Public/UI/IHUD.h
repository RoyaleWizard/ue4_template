// Copyright 2018, Colby Hall. All Rights Reserved.

#pragma once

#include "Core.h"
#include "GameFramework/HUD.h"
#include "IHUD.generated.h"

/**
 * 
 */
UCLASS(Abstract, HideCategories = ("Actor Tick", LOD))
class BLISS_API AIHUD : public AHUD
{
	GENERATED_BODY()

protected:
	/**
	* Class that this HUD will instantiate on BeginPlay
	*
	* @see WidgetInstance
	* @see BeginPlay
	* @protected
	*/
	UPROPERTY(EditDefaultsOnly, Category = HUD)
	TSubclassOf<UUserWidget> WidgetClass;	

	/**
	 * Instance of WidgetClass
	 *
	 * @see WidgetClass
	 * @protected
	 */
	UPROPERTY(Transient)
	UUserWidget* WidgetInstance;

	virtual void BeginPlay() override;
	virtual void Destroyed() override;
};
