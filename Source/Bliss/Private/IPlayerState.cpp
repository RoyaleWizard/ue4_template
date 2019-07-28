// Copyright 2018, Colby Hall. All Rights Reserved.

#include "IPlayerState.h"
#include "ILobbyMap.h"
#include "IPlayerHUD.h"
#include "IPlayerController.h"
#include "IGameInstance.h"
#include "UnrealNetwork.h"

AIPlayerState::AIPlayerState()
{

}

void AIPlayerState::ServerRPCSetSelectedZone_Implementation(const EZoneEnum Zone)
{
	UIGameInstance* ServerIGI = Cast<UIGameInstance>(GetGameInstance());
	if (ServerIGI && HasAuthority())
	{
		ServerIGI->SelectedZone = Zone;
		GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Orange, FString::Printf(TEXT("ServerRPC Zone: %s"), *GETENUMSTRING("EZoneEnum", Zone)));
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, TEXT("ServerRPC Not Firing"));
	
}

bool AIPlayerState::ServerRPCSetSelectedZone_Validate(const EZoneEnum Zone)
{
	return true;
}

void AIPlayerState::ClientRPCSetSelectedZone_Implementation()
{
	UIGameInstance* ClientIGI = Cast<UIGameInstance>(GetGameInstance());
	if (ClientIGI && !HasAuthority())
	{
		Zone = ClientIGI->SelectedZone;
		GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::White, FString::Printf(TEXT("ClientRPC Zone: %s"), *GETENUMSTRING("EZoneEnum", Zone)));
		ServerRPCSetSelectedZone(Zone);
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, TEXT("ClientRPC Not Firing"));
	
}

bool AIPlayerState::ClientRPCSetSelectedZone_Validate()
{
	return true;
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


