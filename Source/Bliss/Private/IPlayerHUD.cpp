// Copyright 2018, Colby Hall. All Rights Reserved.

#include "IPlayerHUD.h"
#include "ILobbyMap.h"
#include "IPlayerState.h"
#include "IPlayerController.h"

//void AIHUD::PostInitializeComponents()
//{
//	Super::PostInitializeComponents();
//
//	if (GEngine && GEngine->GameViewport) // make sure our screen is ready for the widget
//	{
//		SAssignNew(LobbyMapWidget, ILobbyMap).OwnerHUD(this); // add the widget and assign it to the var
//		GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(LobbyMapWidget.ToSharedRef()));
//	}
//}

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

void AIPlayerHUD::OpenMap()
{
	if (MapWidgetInstance)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Hi"));
		CloseMap();
		return;
	}

	if (MapWidgetClass)
	{
		MapWidgetInstance = CreateWidget<UUserWidget>(GetWorld()->GetGameInstance(), MapWidgetClass);

		if (MapWidgetInstance)
		{
			MapWidgetInstance->AddToViewport();
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

	if (WidgetInstance)
	{
		WidgetInstance->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AIPlayerHUD::CloseMap()
{
	if (MapWidgetInstance)
	{
		MapWidgetInstance->RemoveFromParent();

		AIPlayerController* IPC = Cast<AIPlayerController>(GetOwningPlayerController());
		if (IPC)
		{
			IPC->SetInputModeForPlaying();
		}
	}

	MapWidgetInstance = nullptr;

	if (WidgetInstance)
	{
		WidgetInstance->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	
	
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

