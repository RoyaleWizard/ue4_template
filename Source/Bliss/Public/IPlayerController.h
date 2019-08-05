// Copyright 2018, Colby Hall. All Rights Reserved.

#pragma once

#include "Bliss.h"
#include "IBasePlayerController.h"
#include "IPlayerController.generated.h"

class AIGameState;

/**
 * 
 */
UCLASS(Abstract)
class BLISS_API AIPlayerController : public AIBasePlayerController
{
	GENERATED_BODY()
	
public:

	AIPlayerController();

protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:

	void OnEscapeMenuPressed();

protected:

	/**
	 * Widget used for the escape menu
	 *
	 * @see OnEscapeMenuPressed
	 */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> EscapeMenuClass;

	/** Stored escape menu widget*/
	UPROPERTY(BlueprintReadOnly)
	UUserWidget* EscapeMenuWidget;

public:

	/**
	 * Opens the escape menu
	 *
	 * @see CloseEscapeMenu
	 */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	void OpenEscapeMenu();

	/**
	 * Closes the escape menu
	 *
	 * @see OpenEscapeMenu
	 */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	void CloseEscapeMenu();

	/**
	 * Returns if the escape menu is open
	 *
	 * Essentially just checks if we have one created
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, BlueprintCosmetic)
	FORCEINLINE bool IsEscapeMenuOpen() const { return EscapeMenuWidget != nullptr; }

	/**
	 * Sets the input mode to the way we want when a menu is open
	 *
	 * @see SetInputMode
	 */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	void SetInputModeForMenuOpen();

	/**
	* Sets the input mode to the way we want when playing
	*
	* @see SetInputMode
	*/
	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	void SetInputModeForPlaying();

	AIGameState* IGS;

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerIncrementPlayerCount(const EZoneEnum Zone); // Increment player count for selected zone on the server 

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerDecrementPlayerCount(const EZoneEnum Zone); // Decrement player count for last selected zone on the server
	
};
