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

	UFUNCTION(Server, Reliable, WithValidation) // for player to player rpc you need to first call the message on the server
	virtual void ServerIncrementZonePlayerCount(const EZoneEnum Zone); // first rpc for the server

	UFUNCTION(NetMulticast, Reliable, WithValidation) // then the server calls the function with a multicast that executes on all clients and the server
	virtual void NetMulticastIncrementZonePlayerCount(const EZoneEnum Zone); // second rpc for all the clients

	UFUNCTION(Server, Reliable, WithValidation) // for player to player rpc you need to first call the message on the server
	virtual void ServerDecrementZonePlayerCount(const EZoneEnum Zone); // first rpc for the server

	UFUNCTION(NetMulticast, Reliable, WithValidation) // then the server calls the function with a multicast that executes on all clients and the server
	virtual void NetMulticastDecrementZonePlayerCount(const EZoneEnum Zone); // second rpc for all the clients

	UFUNCTION(Server, Reliable, WithValidation)
	virtual void ServerSetSelectedZone(const EZoneEnum Zone);

	UPROPERTY(BlueprintReadOnly, Category = "Zone")
	EZoneEnum SelectedZone;

protected:
	// Used to copy properties from the current PlayerState to the passed one
	virtual void CopyProperties(class APlayerState* PlayerState) override;

	// Used to override the current PlayerState with the properties of the passed one
	virtual void OverrideWith(class APlayerState* PlayerState) override;
	
	
};
