// Copyright 2018, Colby Hall. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "IGameState.generated.h"

/**
 * 
 */
UCLASS()
class BLISS_API AIGameState : public AGameState
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Zone")
	int32 White_PlayerCount = 0;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Zone")
	int32 Green_PlayerCount = 0;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Zone")
	int32 Red_PlayerCount = 0;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Zone")
	int32 Yellow_PlayerCount = 0;

	UFUNCTION()
	virtual void IncrementPlayerCount(const EZoneEnum Zone); // Increment player count for selected zone on the server 

	UFUNCTION()
	virtual void DecrementPlayerCount(const EZoneEnum Zone); // Decrement player count for last selected zone on the server
	
};
