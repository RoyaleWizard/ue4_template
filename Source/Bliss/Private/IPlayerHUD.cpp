// Copyright 2018, Colby Hall. All Rights Reserved.

#include "IPlayerHUD.h"


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

void AIPlayerHUD::Destroyed()
{
	Super::Destroyed();

	if (InventoryWidgetInstance)
	{
		InventoryWidgetInstance->RemoveFromParent();
	}
}

