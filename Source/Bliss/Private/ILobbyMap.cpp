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
		Button_White->OnClicked.AddDynamic(this, &UILobbyMap::WhiteSelected);
	}

	if (Button_Green)
	{
		Button_Green->OnClicked.AddDynamic(this, &UILobbyMap::GreenSelected);
	}

	if (Button_Red)
	{
		Button_Red->OnClicked.AddDynamic(this, &UILobbyMap::RedSelected);
	}

	if (Button_Yellow)
	{
		Button_Yellow->OnClicked.AddDynamic(this, &UILobbyMap::YellowSelected);
	}


	return true;
}

void UILobbyMap::WhiteSelected()
{
	if (!GetWorld() || WhiteFlag)
		return;

	ResetGreenSelection();
	ResetRedSelection();
	ResetYellowSelection();

	if (!IGI)
		return;

	IGI->SelectedZone = "White";
	GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, IGI->SelectedZone);
	FString PlayerCountString = PlayerCount_White->GetText().ToString();
	int32 PlayerCountInt = FCString::Atoi(*PlayerCountString);
	PlayerCountInt++;
	WhiteFlag = true;
	PlayerCountString = FString::FromInt(PlayerCountInt);
	PlayerCount_White->SetText(FText::FromString(PlayerCountString));

}

void UILobbyMap::GreenSelected()
{
	if (!GetWorld() || GreenFlag)
		return;

	ResetWhiteSelection();
	ResetRedSelection();
	ResetYellowSelection();

	if (!IGI)
		return;

	IGI->SelectedZone = "Green";
	GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, IGI->SelectedZone);
	FString PlayerCountString = PlayerCount_Green->GetText().ToString();
	int32 PlayerCountInt = FCString::Atoi(*PlayerCountString);
	PlayerCountInt++;
	GreenFlag = true;
	PlayerCountString = FString::FromInt(PlayerCountInt);
	PlayerCount_Green->SetText(FText::FromString(PlayerCountString));
}

void UILobbyMap::RedSelected()
{
	if (!GetWorld() || RedFlag)
		return;

	ResetWhiteSelection();
	ResetGreenSelection();
	ResetYellowSelection();

	if (!IGI)
		return;

	IGI->SelectedZone = "Red";
	GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, IGI->SelectedZone);
	FString PlayerCountString = PlayerCount_Red->GetText().ToString();
	int32 PlayerCountInt = FCString::Atoi(*PlayerCountString);
	PlayerCountInt++;
	RedFlag = true;
	PlayerCountString = FString::FromInt(PlayerCountInt);
	PlayerCount_Red->SetText(FText::FromString(PlayerCountString));
}

void UILobbyMap::YellowSelected()
{
	if (!GetWorld() || YellowFlag)
		return;

	ResetWhiteSelection();
	ResetGreenSelection();
	ResetRedSelection();

	if (!IGI)
		return;

	IGI->SelectedZone = "Yellow";
	GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, IGI->SelectedZone);
	FString PlayerCountString = PlayerCount_Yellow->GetText().ToString();
	int32 PlayerCountInt = FCString::Atoi(*PlayerCountString);
	PlayerCountInt++;
	YellowFlag = true;
	PlayerCountString = FString::FromInt(PlayerCountInt);
	PlayerCount_Yellow->SetText(FText::FromString(PlayerCountString));
}

void UILobbyMap::ResetWhiteSelection()
{
	if (WhiteFlag)
	{
		FString PlayerCountString = PlayerCount_White->GetText().ToString();
		int32 PlayerCountInt = FCString::Atoi(*PlayerCountString);
		PlayerCountInt--;
		WhiteFlag = false;
		PlayerCountString = FString::FromInt(PlayerCountInt);
		PlayerCount_White->SetText(FText::FromString(PlayerCountString));
	}
}

void UILobbyMap::ResetGreenSelection()
{
	if (GreenFlag)
	{
		FString PlayerCountString = PlayerCount_Green->GetText().ToString();
		int32 PlayerCountInt = FCString::Atoi(*PlayerCountString);
		PlayerCountInt--;
		GreenFlag = false;
		PlayerCountString = FString::FromInt(PlayerCountInt);
		PlayerCount_Green->SetText(FText::FromString(PlayerCountString));
	}
}

void UILobbyMap::ResetRedSelection()
{
	if (RedFlag)
	{
		FString PlayerCountString = PlayerCount_Red->GetText().ToString();
		int32 PlayerCountInt = FCString::Atoi(*PlayerCountString);
		PlayerCountInt--;
		RedFlag = false;
		PlayerCountString = FString::FromInt(PlayerCountInt);
		PlayerCount_Red->SetText(FText::FromString(PlayerCountString));
	}
}

void UILobbyMap::ResetYellowSelection()
{
	if (YellowFlag)
	{
		FString PlayerCountString = PlayerCount_Yellow->GetText().ToString();
		int32 PlayerCountInt = FCString::Atoi(*PlayerCountString);
		PlayerCountInt--;
		YellowFlag = false;
		PlayerCountString = FString::FromInt(PlayerCountInt);
		PlayerCount_Yellow->SetText(FText::FromString(PlayerCountString));
	}
}

void UILobbyMap::UpdateZonePlayerCount(const FString& PlayerCount, const FString& ZoneName)
{
	switch (ZoneName)
	{
	case "White":
		PlayerCount_White->SetText(FText::FromString(PlayerCount));

	case "Green":
		PlayerCount_White->SetText(FText::FromString(PlayerCount));

	case "Red":
		PlayerCount_Red->SetText(FText::FromString(PlayerCount));

	case "Yellow":
		PlayerCount_Yellow->SetText(FText::FromString(PlayerCount));

	default:
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Red, TEXT("Invalid zone name"));
	}
}
