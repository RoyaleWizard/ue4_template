// Copyright 2018, Colby Hall. All Rights Reserved.


#include "ILobbyMap.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "CString.h"
#include "IGameInstance.h"
#include "IPlayerState.h"
#include "IPlayerController.h"

bool UILobbyMap::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success)
		return false;

	IPC = Cast<AIPlayerController>(GetOwningPlayer());

	if (IPC)
	{
		IPS = Cast<AIPlayerState>(IPC->PlayerState);
	}
		

	if (White_Button)
	{
		White_Button->OnClicked.AddDynamic(this, &UILobbyMap::WhiteZoneSelected);
	}

	if (Green_Button)
	{
		Green_Button->OnClicked.AddDynamic(this, &UILobbyMap::GreenZoneSelected);
	}

	if (Red_Button)
	{
		Red_Button->OnClicked.AddDynamic(this, &UILobbyMap::RedZoneSelected);
	}

	if (Yellow_Button)
	{
		Yellow_Button->OnClicked.AddDynamic(this, &UILobbyMap::YellowZoneSelected);
	}

	return true;
}

void UILobbyMap::ResetSelectedZoneButtonBGColor(EZoneEnum Zone)
{
	switch (Zone)
	{
	case EZoneEnum::ZE_White:
		White_Button->SetBackgroundColor(FColor::White);
		break;

	case EZoneEnum::ZE_Green:
		Green_Button->SetBackgroundColor(FColor::White);
		break;

	case EZoneEnum::ZE_Red:
		Red_Button->SetBackgroundColor(FColor::White);
		break;

	case EZoneEnum::ZE_Yellow:
		Yellow_Button->SetBackgroundColor(FColor::White);
		break;

	default:
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Red, TEXT("Invalid zone button to reset background color for"));
	}
}

void UILobbyMap::WhiteZoneSelected()
{
	if (!GetWorld() || CurrentSelectedZone == EZoneEnum::ZE_White) // If the current zone is selected again ignore that
		return;
	
	if (IPS && CurrentSelectedZone != EZoneEnum::ZE_NULL)
	{
		ResetSelectedZoneButtonBGColor(CurrentSelectedZone); // Make sure to reset the current selected zone button background color
		IPS->ServerDecrementZonePlayerCount(CurrentSelectedZone); // Make sure to decrement the current selected zone's player count
	}
	

	CurrentSelectedZone = EZoneEnum::ZE_White; // Set White zone as the current selected zone
	IPS->SelectedZone = EZoneEnum::ZE_White;

	if (IPS && CurrentSelectedZone != EZoneEnum::ZE_NULL)
	{
		White_Button->SetBackgroundColor(FColor::Green);
		IPS->ServerIncrementZonePlayerCount(CurrentSelectedZone); // Add to the current selected zone's player count using server rpc
		IPS->ServerSetSelectedZone(CurrentSelectedZone);
	}
	
}

void UILobbyMap::GreenZoneSelected()
{
	if (!GetWorld() || CurrentSelectedZone == EZoneEnum::ZE_Green) // If the current zone is selected again ignore that
		return;

	if (IPS && CurrentSelectedZone != EZoneEnum::ZE_NULL)
	{
		ResetSelectedZoneButtonBGColor(CurrentSelectedZone); // Make sure to reset the current selected zone button background color
		IPS->ServerDecrementZonePlayerCount(CurrentSelectedZone); // Make sure to decrement the current selected zone's player count
	}

	CurrentSelectedZone = EZoneEnum::ZE_Green; // Set Green zone as the current selected zone
	IPS->SelectedZone = CurrentSelectedZone;

	if (IPS && CurrentSelectedZone != EZoneEnum::ZE_NULL)
	{
		Green_Button->SetBackgroundColor(FColor::Green);
		IPS->ServerIncrementZonePlayerCount(CurrentSelectedZone); // Add to the current selected zone's player count using server rpc
		IPS->ServerSetSelectedZone(CurrentSelectedZone);
	}
}

void UILobbyMap::RedZoneSelected()
{
	if (!GetWorld() || CurrentSelectedZone == EZoneEnum::ZE_Red) // If the current zone is selected again ignore that
		return;

	if (IPS && CurrentSelectedZone != EZoneEnum::ZE_NULL)
	{
		ResetSelectedZoneButtonBGColor(CurrentSelectedZone); // Make sure to reset the current selected zone button background color
		IPS->ServerDecrementZonePlayerCount(CurrentSelectedZone); // Make sure to decrement the current selected zone's player count
	}

	CurrentSelectedZone = EZoneEnum::ZE_Red; // Set Red zone as the current selected zone
	IPS->SelectedZone = EZoneEnum::ZE_Red;
	
	if (IPS && CurrentSelectedZone != EZoneEnum::ZE_NULL)
	{
		Red_Button->SetBackgroundColor(FColor::Green);
		IPS->ServerIncrementZonePlayerCount(CurrentSelectedZone); // Add to the current selected zone's player count using server rpc
		IPS->ServerSetSelectedZone(CurrentSelectedZone);
	}
}

void UILobbyMap::YellowZoneSelected()
{
	if (!GetWorld() || CurrentSelectedZone == EZoneEnum::ZE_Yellow) // If the current zone is selected again ignore that
		return;

	if (IPS && CurrentSelectedZone != EZoneEnum::ZE_NULL)
	{
		ResetSelectedZoneButtonBGColor(CurrentSelectedZone); // Make sure to reset the current selected zone button background color
		IPS->ServerDecrementZonePlayerCount(CurrentSelectedZone); // Make sure to decrement the current selected zone's player count
	}

	CurrentSelectedZone = EZoneEnum::ZE_Yellow; // Set Yellow zone as the current selected zone
	IPS->SelectedZone = EZoneEnum::ZE_Yellow;

	if (IPS && CurrentSelectedZone != EZoneEnum::ZE_NULL)
	{
		Yellow_Button->SetBackgroundColor(FColor::Green);
		IPS->ServerIncrementZonePlayerCount(CurrentSelectedZone); // Add to the current selected zone's player count using server rpc
		IPS->ServerSetSelectedZone(CurrentSelectedZone);
	}
}

void UILobbyMap::IncrementZonePlayerCount(const EZoneEnum Zone)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Blue, FString::Printf(TEXT("Zone: %s"), *GETENUMSTRING("EZoneEnum", Zone)));

	switch (Zone)
	{
	case EZoneEnum::ZE_White:
		Zone_PlayerCount = White_PlayerCount;
		break;

	case EZoneEnum::ZE_Green:
		Zone_PlayerCount = Green_PlayerCount;
		break;

	case EZoneEnum::ZE_Red:
		Zone_PlayerCount = Red_PlayerCount;
		break;

	case EZoneEnum::ZE_Yellow:
		Zone_PlayerCount = Yellow_PlayerCount;
		break;

	default:
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Red, TEXT("Invalid zone to Increment to"));
		IPS->SelectedZone = EZoneEnum::ZE_NULL;
		Zone_PlayerCount = nullptr;
	}

	GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, *GETENUMSTRING("EZoneEnum", IPS->SelectedZone));
	if (!Zone_PlayerCount)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Red, TEXT("Invalid Ptr to UTextBlock"));
		return;
	}

	FString PlayerCountString = Zone_PlayerCount->GetText().ToString();
	int32 PlayerCountInt = FCString::Atoi(*PlayerCountString);
	PlayerCountInt++;
	PlayerCountString = FString::FromInt(PlayerCountInt);
	Zone_PlayerCount->SetText(FText::FromString(PlayerCountString));
}

void UILobbyMap::DecrementZonePlayerCount(const EZoneEnum Zone)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Orange, FString::Printf(TEXT("Zone: %s"), *GETENUMSTRING("EZoneEnum", Zone)));

	switch (Zone)
	{
	case EZoneEnum::ZE_White:
		Zone_PlayerCount = White_PlayerCount;
		break;
	
	case EZoneEnum::ZE_Green:
		Zone_PlayerCount = Green_PlayerCount;
		break;

	case EZoneEnum::ZE_Red:
		Zone_PlayerCount = Red_PlayerCount;
		break;

	case EZoneEnum::ZE_Yellow:
		Zone_PlayerCount = Yellow_PlayerCount;
		break;

	default:
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Red, TEXT("Invalid zone to decrement from"));
		Zone_PlayerCount = nullptr;
	}

	if (!Zone_PlayerCount)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Purple, TEXT("Invalid Ptr to UTextBlock"));
		return;
	}

	FString PlayerCountString = Zone_PlayerCount->GetText().ToString();
	int32 PlayerCountInt = FCString::Atoi(*PlayerCountString);
	PlayerCountInt--;
	PlayerCountString = FString::FromInt(PlayerCountInt);
	Zone_PlayerCount->SetText(FText::FromString(PlayerCountString));
}
