// Copyright 2018, Colby Hall. All Rights Reserved.

#include "IPlayerHUD.h"
#include "ILobbyMap.h"
#include "IPlayerState.h"
#include "IPlayerController.h"

void AIPlayerHUD::OpenInventory()
{
	if (InventoryWidgetClass)
	{
		InventoryWidgetInstance = CreateWidget<UUserWidget>(GetWorld()->GetGameInstance(), InventoryWidgetClass);

		if (InventoryWidgetInstance)
		{
			InventoryWidgetInstance->AddToViewport();
		}
		else
		{
			UE_LOG(LogBlissHUD, Warning, TEXT("Failed to create inventory widget %s on HUD %s"), *InventoryWidgetClass->GetName(), *GetClass()->GetName());
		}
	}
	else
	{
		UE_LOG(LogBlissHUD, Warning, TEXT("HUD %s does not have a WidgetClass"), *GetClass()->GetName());
	}

	if (WidgetInstance)
	{
		WidgetInstance->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AIPlayerHUD::CloseInventory()
{
	if (InventoryWidgetInstance)
	{
		InventoryWidgetInstance->RemoveFromParent();
	}

	InventoryWidgetInstance = nullptr;

	if (WidgetInstance)
	{
		WidgetInstance->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

void AIPlayerHUD::ToggleMap()
{
	AIPlayerController* IPC = Cast<AIPlayerController>(GetOwningPlayerController());
	if (!IPC) 
		return;
	
	if (MapWidgetInstance && MapWidgetInstance->GetVisibility() == ESlateVisibility::Visible)
	{
		MapWidgetInstance->RemoveFromParent();
		MapWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
		IPC->SetInputModeForPlaying();
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Map Closed!"));
		return;
	}
	else if (MapWidgetInstance && MapWidgetInstance->GetVisibility() == ESlateVisibility::Hidden)
	{
		MapWidgetInstance->AddToViewport();
		MapWidgetInstance->SetVisibility(ESlateVisibility::Visible);
		IPC->SetInputModeForMenuOpen();
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Map Open!"));
		return;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("No map instance found. let's create one!")); // First time opening the map
	}
	

	if (MapWidgetClass)
	{
		MapWidgetInstance = CreateWidget<UILobbyMap>(GetWorld()->GetGameInstance(), MapWidgetClass);

		if (MapWidgetInstance)
		{
			MapWidgetInstance->AddToViewport();
			IPC->SetInputModeForMenuOpen();
			MapWidgetInstance->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			UE_LOG(LogBlissHUD, Warning, TEXT("Failed to create map widget %s on HUD %s"), *MapWidgetClass->GetName(), *GetClass()->GetName());
		}
	}
	else
	{
		UE_LOG(LogBlissHUD, Warning, TEXT("HUD %s does not have a WidgetClass"), *GetClass()->GetName());
	}

	/*if (WidgetInstance)
	{
		WidgetInstance->SetVisibility(ESlateVisibility::Hidden);
	}*/
}

void AIPlayerHUD::Destroyed()
{
	Super::Destroyed();

	if (InventoryWidgetInstance)
	{
		InventoryWidgetInstance->RemoveFromParent();
	}

	if (MapWidgetInstance)
	{
		MapWidgetInstance->RemoveFromParent();
	}
}

