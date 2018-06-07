// Copyright 2018, Colby Hall. All Rights Reserved.

#include "IPlayerController.h"
#include "Core/IGameInstance.h"

void AIPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UIGameInstance* GameInstance = Cast<UIGameInstance>(GetGameInstance());
	if (GameInstance && IsLocalPlayerController())
	{
		GameInstance->OnEndLoadingScreen();
	}

}


