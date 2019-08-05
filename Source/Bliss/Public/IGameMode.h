// Copyright 2018, Colby Hall. All Rights Reserved.

#pragma once

#include "Core.h"
#include "IBaseGameMode.h"
#include "IGameMode.generated.h"

class APlayerStart;

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

	/** always */
	//virtual bool PlayerCanRestart_Implementation(APlayerController* Player) override;

	/** check if player can use spawn point */
	virtual bool IsSpawnpointAllowed(APlayerStart* SpawnPoint, AController* Player) const;

	/** Return true if FindPlayerStart should use the StartSpot stored on Player instead of calling ChoosePlayerStart */
	virtual bool ShouldSpawnAtStartSpot(AController* Player) override;
	
	//virtual void PostLogin(APlayerController* NewPlayer) override;
	
};
