// Copyright 2018, Colby Hall. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "IPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class BLISS_API AIPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AIPlayerState();

	UFUNCTION(Server, Reliable, WithValidation) // for player to player rpc you need to first call the function on the server
	virtual void ServerSetSelectedZone(const EZoneEnum Zone); // first rpc for the server
	
	UFUNCTION(NetMulticast, Reliable, WithValidation) // then the server calls the function with a multicast that executes on all clients and the server
	virtual void MulticastSetSelectedZone(const EZoneEnum Zone); // second rpc for all the clients

	UFUNCTION(Server, Reliable, WithValidation) // for player to player rpc you need to first call the function on the server
	virtual void ServerClearZoneSelection(const EZoneEnum Zone); // first rpc for the server

	UFUNCTION(NetMulticast, Reliable, WithValidation) // then the server calls the function with a multicast that executes on all clients and the server
	virtual void MulticastClearZoneSelection(const EZoneEnum Zone); // second rpc for all the clients

	UPROPERTY(BlueprintReadOnly, Category = "Zone")
	EZoneEnum SelectedZone;

protected:
	// Used to copy properties from the current PlayerState to the passed one
	virtual void CopyProperties(class APlayerState* PlayerState) override;

	// Used to override the current PlayerState with the properties of the passed one
	virtual void OverrideWith(class APlayerState* PlayerState) override;
	
	
};
