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
	virtual void ServerRPCIncrementZonePlayerCount(const EZoneEnum Zone); // first rpc for the server

	UFUNCTION(NetMulticast, Reliable, WithValidation) // then the server calls the function with a multicast that executes on all clients and the server
	virtual void NetMulticastRPCIncrementZonePlayerCount(const EZoneEnum Zone); // second rpc for all the clients

	UFUNCTION(Server, Reliable, WithValidation) // for player to player rpc you need to first call the message on the server
	virtual void ServerRPCDecrementZonePlayerCount(const EZoneEnum Zone); // first rpc for the server

	UFUNCTION(NetMulticast, Reliable, WithValidation) // then the server calls the function with a multicast that executes on all clients and the server
	virtual void NetMulticastRPCDecrementZonePlayerCount(const EZoneEnum Zone); // second rpc for all the clients

	UFUNCTION(Client, Reliable, WithValidation)
	virtual void ClientRPCSetSelectedZone();

	UFUNCTION(Server, Reliable, WithValidation)
	virtual void ServerRPCSetSelectedZone(const EZoneEnum Zone);

	UPROPERTY()
	EZoneEnum Zone;
	
	
};
