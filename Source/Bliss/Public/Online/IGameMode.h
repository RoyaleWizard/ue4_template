// Copyright 2018, Colby Hall. All Rights Reserved.

#pragma once

#include "Core.h"
#include "GameFramework/GameMode.h"
#include "IGameMode.generated.h"

/**
 * 
 */
UCLASS(HideCategories=(LOD, "Actor Tick"))
class BLISS_API AIGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	// Default Constructor
	AIGameMode();
	
};
