// Copyright 2018, Colby Hall. All Rights Reserved.

#include "IPlayerState.h"
#include "ILobbyMap.h"
#include "IPlayerHUD.h"
#include "IPlayerController.h"

AIPlayerState::AIPlayerState()
{

}

void AIPlayerState::CopyProperties(class APlayerState* NewPlayerState)
{
	Super::CopyProperties(NewPlayerState);

	if (NewPlayerState)
	{
		AIPlayerState* IPC = Cast<AIPlayerState>(NewPlayerState);
		if (IPC)
			IPC->SelectedZone = SelectedZone;
	}
}

void AIPlayerState::OverrideWith(class APlayerState* OldPlayerState)
{
	Super::OverrideWith(OldPlayerState);

	if (OldPlayerState)
	{
		AIPlayerState* IPC = Cast<AIPlayerState>(OldPlayerState);
		if (IPC)
			SelectedZone = IPC->SelectedZone;
	}
}

void AIPlayerState::ServerSetSelectedZone_Implementation(const EZoneEnum Zone)
{
	this->SelectedZone = Zone;
	GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Orange, FString::Printf(TEXT("ServerRPC Zone: %s"), *GETENUMSTRING("EZoneEnum", SelectedZone)));
	//GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, TEXT("ServerRPC Not Firing"));
}

bool AIPlayerState::ServerSetSelectedZone_Validate(const EZoneEnum Zone)
{
	return true;
}

void AIPlayerState::NetMulticastDecrementZonePlayerCount_Implementation(const EZoneEnum Zone)
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

bool AIPlayerState::NetMulticastDecrementZonePlayerCount_Validate(const EZoneEnum Zone)
{
	return true;
}

void AIPlayerState::ServerDecrementZonePlayerCount_Implementation(const EZoneEnum Zone)
{
	NetMulticastDecrementZonePlayerCount(Zone);
}

bool AIPlayerState::ServerDecrementZonePlayerCount_Validate(const EZoneEnum Zone)
{
	return true;
}

void AIPlayerState::ServerIncrementZonePlayerCount_Implementation(const EZoneEnum Zone)
{
	NetMulticastIncrementZonePlayerCount(Zone);
}

bool AIPlayerState::ServerIncrementZonePlayerCount_Validate(const EZoneEnum Zone)
{
	return true;
}

void AIPlayerState::NetMulticastIncrementZonePlayerCount_Implementation(const EZoneEnum Zone)
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

bool AIPlayerState::NetMulticastIncrementZonePlayerCount_Validate(const EZoneEnum Zone)
{
	return true;
}


