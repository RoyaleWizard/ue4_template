// Copyright 2018, Colby Hall. All Rights Reserved.

#pragma once

#include "Core.h"
#include "Engine/GameInstance.h"
#include "ILobbyMap.h"
#include "IGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BLISS_API UIGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:

	UFUNCTION()
	void OnBeginLoadingScreen(const FString& MapName);

	TSharedPtr<class SBlissLoadingScreen> LoadingScreenWidget;

public:

	virtual void Init() override;
	
	UFUNCTION()
	void OnEndLoadingScreen();
};
