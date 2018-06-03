// Copyright 2018, Colby Hall. All Rights Reserved.

#include "IHUD.h"
#include "Bliss.h"


void AIHUD::BeginPlay()
{
	Super::BeginPlay();

	if (WidgetClass)
	{
		WidgetInstance = CreateWidget<UUserWidget>(GetWorld()->GetGameInstance(), WidgetClass);

		if (WidgetInstance)
		{
			WidgetInstance->AddToViewport();
		}
		else
		{
			UE_LOG(LogBlissHUD, Warning, TEXT("Failed to create widget %s on HUD %s"), *WidgetClass->GetName(), *GetClass()->GetName());
		}
	}
	else
	{
		UE_LOG(LogBlissHUD, Warning, TEXT("HUD %s does not have a WidgetClass"), *GetClass()->GetName());
	}
}

void AIHUD::Destroyed()
{
	Super::Destroyed();

	if (WidgetInstance)
	{
		WidgetInstance->RemoveFromParent();
	}
}

