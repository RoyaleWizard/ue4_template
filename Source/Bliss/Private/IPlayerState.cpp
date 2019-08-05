// Copyright 2018, Colby Hall. All Rights Reserved.

#include "IPlayerState.h"
#include "ILobbyMap.h"
#include "IPlayerHUD.h"
#include "IPlayerController.h"

//#include "Net/UnrealNetwork.h"

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
	GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Orange, FString::Printf(TEXT("PS ServerRPC Zone: %s"), *GETENUMSTRING("EZoneEnum", SelectedZone)));
	MulticastSetSelectedZone(Zone);
}

bool AIPlayerState::ServerSetSelectedZone_Validate(const EZoneEnum Zone)
{
	return true;
}

void AIPlayerState::MulticastSetSelectedZone_Implementation(const EZoneEnum Zone)
{
	AIPlayerController* IPC;
	AIPlayerHUD* IPHUD;

	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator) // find all controllers
	{
		IPC = Cast<AIPlayerController>(*Iterator);
		if (IPC)
		{
			IPHUD = Cast<AIPlayerHUD>(IPC->GetHUD());
			if (IPHUD && IPHUD->MapWidgetInstance)
				IPHUD->MapWidgetInstance->SetSelectedZone(Zone); // Increment zone count on this player controller
		}
	}
}

bool AIPlayerState::MulticastSetSelectedZone_Validate(const EZoneEnum Zone)
{
	return true;
}

void AIPlayerState::ServerClearZoneSelection_Implementation(const EZoneEnum Zone)
{
	MulticastClearZoneSelection(Zone);
}

bool AIPlayerState::ServerClearZoneSelection_Validate(const EZoneEnum Zone)
{
	return true;
}

void AIPlayerState::MulticastClearZoneSelection_Implementation(const EZoneEnum Zone)
{
	AIPlayerController* IPC;
	AIPlayerHUD* IPHUD;

	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator) // find all controllers
	{
		IPC = Cast<AIPlayerController>(*Iterator);
		if (IPC)
		{
			IPHUD = Cast<AIPlayerHUD>(IPC->GetHUD());
			if (IPHUD && IPHUD->MapWidgetInstance)
				IPHUD->MapWidgetInstance->ClearZoneSelection(Zone); // Clear selection on this player controller
		}
	}
}

bool AIPlayerState::MulticastClearZoneSelection_Validate(const EZoneEnum Zone)
{
	return true;
}

