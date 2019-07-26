// Copyright 2018, Colby Hall. All Rights Reserved.

#include "IPlayerState.h"
#include "ILobbyMap.h"
#include "IPlayerHUD.h"
#include "IPlayerController.h"

AIPlayerState::AIPlayerState()
{

}

void AIPlayerState::NetMulticastRPCDecrementZonePlayerCount_Implementation(const EZoneEnum Zone)
{
	AIPlayerController* IPC;
	AIPlayerHUD* IPHUD;

	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator) // find all controllers
	{
		IPC = Cast<AIPlayerController>(*Iterator);
		if (IPC)
		{
			IPHUD = Cast<AIPlayerHUD>(IPC->GetHUD());
			if (IPHUD && IPHUD->MapWidgetInstance->bIsEnabled)
				IPHUD->MapWidgetInstance->DecrementZonePlayerCount(Zone); // place the chat message on this player controller
		}
	}
}

bool AIPlayerState::NetMulticastRPCDecrementZonePlayerCount_Validate(const EZoneEnum Zone)
{
	return true;
}

void AIPlayerState::ServerRPCDecrementZonePlayerCount_Implementation(const EZoneEnum Zone)
{
	NetMulticastRPCDecrementZonePlayerCount(Zone);
}

bool AIPlayerState::ServerRPCDecrementZonePlayerCount_Validate(const EZoneEnum Zone)
{
	return true;
}

void AIPlayerState::ServerRPCIncrementZonePlayerCount_Implementation(const EZoneEnum Zone)
{
	NetMulticastRPCIncrementZonePlayerCount(Zone);
}

bool AIPlayerState::ServerRPCIncrementZonePlayerCount_Validate(const EZoneEnum Zone)
{
	return true;
}

void AIPlayerState::NetMulticastRPCIncrementZonePlayerCount_Implementation(const EZoneEnum Zone)
{
	AIPlayerController* IPC;
	AIPlayerHUD* IPHUD;

	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator) // find all controllers
	{
		IPC = Cast<AIPlayerController>(*Iterator);
		if (IPC)
		{
			IPHUD = Cast<AIPlayerHUD>(IPC->GetHUD());
			if (IPHUD && IPHUD->MapWidgetInstance->bIsEnabled)
				IPHUD->MapWidgetInstance->IncrementZonePlayerCount(Zone); // place the chat message on this player controller
		}
	}
}

bool AIPlayerState::NetMulticastRPCIncrementZonePlayerCount_Validate(const EZoneEnum Zone)
{
	return true;
}


