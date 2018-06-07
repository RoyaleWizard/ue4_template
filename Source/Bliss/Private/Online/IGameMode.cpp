// Copyright 2018, Colby Hall. All Rights Reserved.

#include "IGameMode.h"
#include "Player/ICharacter.h"
#include "Player/IPlayerController.h"
#include "UI/IHUD.h"

AIGameMode::AIGameMode()
{
	DefaultPawnClass = AICharacter::StaticClass();
	PlayerControllerClass = AIPlayerController::StaticClass();
	HUDClass = AIHUD::StaticClass();
}

