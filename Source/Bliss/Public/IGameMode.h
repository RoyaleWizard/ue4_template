// Copyright 2018, Colby Hall. All Rights Reserved.

#pragma once

#include "Core.h"
#include "IBaseGameMode.h"
#include "IGameMode.generated.h"

/**
 * 
 */
UCLASS(HideCategories=(LOD, "Actor Tick"), Abstract)
class BLISS_API AIGameMode : public AIBaseGameMode
{
	GENERATED_BODY()

public:

	// Default Constructor
	AIGameMode();

	/** select best spawn point for player */
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	
};
