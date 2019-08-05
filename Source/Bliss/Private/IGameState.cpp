// Copyright 2018, Colby Hall. All Rights Reserved.

#include "IGameState.h"

#include "ILobbyMap.h"

#include "Net/UnrealNetwork.h"


void AIGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AIGameState, White_PlayerCount);
	DOREPLIFETIME(AIGameState, Green_PlayerCount);
	DOREPLIFETIME(AIGameState, Red_PlayerCount);
	DOREPLIFETIME(AIGameState, Yellow_PlayerCount);
}

void AIGameState::IncrementPlayerCount(const EZoneEnum Zone)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Orange, FString::Printf(TEXT("GS ServerRPC Zone: %s"), *GETENUMSTRING("EZoneEnum", Zone)));
	switch (Zone)
	{
	case EZoneEnum::ZE_White:
		White_PlayerCount++;
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Cyan, TEXT("Setting White in Switch"));
		break;

	case EZoneEnum::ZE_Green:
		Green_PlayerCount++;
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Cyan, TEXT("Setting Green in Switch"));
		break;

	case EZoneEnum::ZE_Red:
		Red_PlayerCount++;
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Cyan, TEXT("Setting Red in Switch"));
		break;

	case EZoneEnum::ZE_Yellow:
		Yellow_PlayerCount++;
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Cyan, TEXT("Setting Yellow in Switch"));
		break;

	default:
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Cyan, TEXT("Invalid zone to increment to"));
	}
}

void AIGameState::DecrementPlayerCount(const EZoneEnum Zone)
{
	switch (Zone)
	{
	case EZoneEnum::ZE_White:
		White_PlayerCount--;
		break;

	case EZoneEnum::ZE_Green:
		Green_PlayerCount--;
		break;

	case EZoneEnum::ZE_Red:
		Red_PlayerCount--;
		break;

	case EZoneEnum::ZE_Yellow:
		Yellow_PlayerCount--;
		break;

	default:
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Red, TEXT("Invalid zone to decrement from"));
	}
}
