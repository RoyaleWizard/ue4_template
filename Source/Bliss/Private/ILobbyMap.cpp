// Copyright 2018, Colby Hall. All Rights Reserved.


#include "ILobbyMap.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "CString.h"
#include "IGameInstance.h"

bool UILobbyMap::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success)
		return false;

	IGI = Cast<UIGameInstance>(GetWorld()->GetGameInstance());

	if (Button_White)
	{
		Button_White->OnClicked.AddDynamic(this, &UILobbyMap::WhiteZoneSelected);
	}

	if (Button_Green)
	{
		Button_Green->OnClicked.AddDynamic(this, &UILobbyMap::GreenZoneSelected);
	}

	if (Button_Red)
	{
		Button_Red->OnClicked.AddDynamic(this, &UILobbyMap::RedZoneSelected);
	}

	if (Button_Yellow)
	{
		Button_Yellow->OnClicked.AddDynamic(this, &UILobbyMap::YellowZoneSelected);
	}

	return true;
}

void UILobbyMap::WhiteZoneSelected()
{
	if (!GetWorld() || CurrentSelectedZone == EZoneEnum::ZE_White) // If the current zone is selected again ignore that
		return;
	
	if (CurrentSelectedZone != EZoneEnum::ZE_NULL)
	{
		RemoveFromPlayerCount(CurrentSelectedZone); // Make sure to remove from the current selected zone's player count
	}
	

	CurrentSelectedZone = EZoneEnum::ZE_White; // Set White zone as the current selected zone

	if (!IGI)
		return;

	AddToPlayerCount(CurrentSelectedZone); //Add to the current selected zone's player count
}

void UILobbyMap::GreenZoneSelected()
{
	if (!GetWorld() || CurrentSelectedZone == EZoneEnum::ZE_Green) // If the current zone is selected again ignore that
		return;

	if (CurrentSelectedZone != EZoneEnum::ZE_NULL)
	{
		RemoveFromPlayerCount(CurrentSelectedZone); // Make sure to remove from the current selected zone's player count
	}

	CurrentSelectedZone = EZoneEnum::ZE_Green; // Set Green zone as the current selected zone

	if (!IGI)
		return;

	AddToPlayerCount(CurrentSelectedZone); //Add to the current selected zone's player count
}

void UILobbyMap::RedZoneSelected()
{
	if (!GetWorld() || CurrentSelectedZone == EZoneEnum::ZE_Red) // If the current zone is selected again ignore that
		return;

	if (CurrentSelectedZone != EZoneEnum::ZE_NULL)
	{
		RemoveFromPlayerCount(CurrentSelectedZone); // Make sure to remove from the current selected zone's player count
	}

	CurrentSelectedZone = EZoneEnum::ZE_Red; // Set Red zone as the current selected zone

	if (!IGI)
		return;

	AddToPlayerCount(CurrentSelectedZone); //Add to the current selected zone's player count
}

void UILobbyMap::YellowZoneSelected()
{
	if (!GetWorld() || CurrentSelectedZone == EZoneEnum::ZE_Yellow) // If the current zone is selected again ignore that
		return;

	if (CurrentSelectedZone != EZoneEnum::ZE_NULL)
	{
		RemoveFromPlayerCount(CurrentSelectedZone); // Make sure to remove from the current selected zone's player count
	}

	CurrentSelectedZone = EZoneEnum::ZE_Yellow; // Set Yellow zone as the current selected zone

	if (!IGI)
		return;

	AddToPlayerCount(CurrentSelectedZone); //Add to the current selected zone's player count
}

//void UILobbyMap::ResetWhiteSelection()
//{
//	if (WhiteFlag)
//	{
//		FString PlayerCountString = PlayerCount_White->GetText().ToString();
//		int32 PlayerCountInt = FCString::Atoi(*PlayerCountString);
//		PlayerCountInt--;
//		WhiteFlag = false;
//		PlayerCountString = FString::FromInt(PlayerCountInt);
//		PlayerCount_White->SetText(FText::FromString(PlayerCountString));
//	}
//}
//
//void UILobbyMap::ResetGreenSelection()
//{
//	if (GreenFlag)
//	{
//		FString PlayerCountString = PlayerCount_Green->GetText().ToString();
//		int32 PlayerCountInt = FCString::Atoi(*PlayerCountString);
//		PlayerCountInt--;
//		GreenFlag = false;
//		PlayerCountString = FString::FromInt(PlayerCountInt);
//		PlayerCount_Green->SetText(FText::FromString(PlayerCountString));
//	}
//}
//
//void UILobbyMap::ResetRedSelection()
//{
//	if (RedFlag)
//	{
//		FString PlayerCountString = PlayerCount_Red->GetText().ToString();
//		int32 PlayerCountInt = FCString::Atoi(*PlayerCountString);
//		PlayerCountInt--;
//		RedFlag = false;
//		PlayerCountString = FString::FromInt(PlayerCountInt);
//		PlayerCount_Red->SetText(FText::FromString(PlayerCountString));
//	}
//}
//
//void UILobbyMap::ResetYellowSelection()
//{
//	if (YellowFlag)
//	{
//		FString PlayerCountString = PlayerCount_Yellow->GetText().ToString();
//		int32 PlayerCountInt = FCString::Atoi(*PlayerCountString);
//		PlayerCountInt--;
//		YellowFlag = false;
//		PlayerCountString = FString::FromInt(PlayerCountInt);
//		PlayerCount_Yellow->SetText(FText::FromString(PlayerCountString));
//	}
//}

void UILobbyMap::AddToPlayerCount(const EZoneEnum Zone)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Blue, FString::Printf(TEXT("Zone: %s"), *GETENUMSTRING("EZoneEnum", Zone)));

	switch (Zone)
	{
	case EZoneEnum::ZE_White:
		IGI->SelectedZone = "White";
		//WhiteFlag = true;
		PlayerCount = PlayerCount_White;
		break;

	case EZoneEnum::ZE_Green:
		IGI->SelectedZone = "Green";
		//GreenFlag = true;
		PlayerCount = PlayerCount_Green;
		break;

	case EZoneEnum::ZE_Red:
		IGI->SelectedZone = "Red";
		//RedFlag = true;
		PlayerCount = PlayerCount_Red;
		break;

	case EZoneEnum::ZE_Yellow:
		IGI->SelectedZone = "Yellow";
		//YellowFlag = true;
		PlayerCount = PlayerCount_Yellow;
		break;

	default:
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Red, TEXT("Invalid zone name to add to"));
		PlayerCount = nullptr;
	}

	GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, IGI->SelectedZone);
	if (!PlayerCount)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Red, TEXT("Invalid Ptr to UTextBlock"));
		return;
	}

	FString PlayerCountString = PlayerCount->GetText().ToString();
	int32 PlayerCountInt = FCString::Atoi(*PlayerCountString);
	PlayerCountInt++;
	PlayerCountString = FString::FromInt(PlayerCountInt);
	PlayerCount->SetText(FText::FromString(PlayerCountString));
}

void UILobbyMap::RemoveFromPlayerCount(const EZoneEnum Zone)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Orange, FString::Printf(TEXT("Zone: %s"), *GETENUMSTRING("EZoneEnum", Zone)));

	switch (Zone)
	{
	case EZoneEnum::ZE_White:
		//WhiteFlag = false;
		PlayerCount = PlayerCount_White;
		break;
	
	case EZoneEnum::ZE_Green:
		//GreenFlag = false;
		PlayerCount = PlayerCount_Green;
		break;

	case EZoneEnum::ZE_Red:
		//RedFlag = false;
		PlayerCount = PlayerCount_Red;
		break;

	case EZoneEnum::ZE_Yellow:
		//YellowFlag = false;
		PlayerCount = PlayerCount_Yellow;
		break;

	default:
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Red, TEXT("Invalid zone name to remove from"));
		PlayerCount = nullptr;
	}

	if (!PlayerCount)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Purple, TEXT("Invalid Ptr to UTextBlock"));
		return;
	}

	FString PlayerCountString = PlayerCount->GetText().ToString();
	int32 PlayerCountInt = FCString::Atoi(*PlayerCountString);
	PlayerCountInt--;
	PlayerCountString = FString::FromInt(PlayerCountInt);
	PlayerCount->SetText(FText::FromString(PlayerCountString));
}
