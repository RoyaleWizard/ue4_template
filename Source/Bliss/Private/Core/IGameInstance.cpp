// Copyright 2018, Colby Hall. All Rights Reserved.

#include "IGameInstance.h"
#include "BlissLoadingScreen.h"

#define LOADING_SCREEN_TEXTURE_PATH ""

void UIGameInstance::Init()
{
	Super::Init();

	if (!IsDedicatedServerInstance())
	{
		GEngine->SetMaxFPS(250);
		FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UIGameInstance::OnBeginLoadingScreen);
		// FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UIGameInstance::OnEndLoadingScreen);
	}

}

void UIGameInstance::OnBeginLoadingScreen(const FString& MapName)
{
	ensure(!IsDedicatedServerInstance());

	IBlissLoadingScreenModule* const LoadingScreenModule = FModuleManager::LoadModulePtr<IBlissLoadingScreenModule>("BlissLoadingScreen");
	if (LoadingScreenModule)
	{
		LoadingScreenModule->StartInGameLoadingScreen(MapName, "");
	}

	LoadingScreenWidget = SNew(SBlissLoadingScreen).TexturePath(LOADING_SCREEN_TEXTURE_PATH);

	UGameViewportClient* ViewportClient = GetGameViewportClient();
	if (ViewportClient)
	{
		ViewportClient->AddViewportWidgetContent(LoadingScreenWidget.ToSharedRef(), 999);
	}
}

void UIGameInstance::OnEndLoadingScreen()
{
	ensure(!IsDedicatedServerInstance());

	UGameViewportClient* ViewportClient = GetGameViewportClient();
	if (ViewportClient)
	{
		ViewportClient->RemoveViewportWidgetContent(LoadingScreenWidget.ToSharedRef());
	}

	LoadingScreenWidget = nullptr;
}
