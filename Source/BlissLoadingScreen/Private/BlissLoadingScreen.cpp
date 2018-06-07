#include "BlissLoadingScreen.h"

#include "SlateBasics.h"
#include "MoviePlayer.h"
#include "Widgets/Layout/SSafeZone.h"
#include "Widgets/Images/SThrobber.h"


void SBlissLoadingScreen::Construct(const FArguments& InArgs)
{
	TexturePath = InArgs._TexturePath;
	if (TexturePath.IsEmpty())
	{
		TexturePath = LOADING_SCREEN_PATH;
	}
	const FName LoadingScreenName(*TexturePath);

	//since we are not using game styles here, just load one image
	LoadingScreenBrush = MakeShareable(new FBlissLoadingScreenBrush(LoadingScreenName, FVector2D(1920, 1080)));

	ChildSlot
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.Image(LoadingScreenBrush.Get())
			]
		];
}

void IBlissLoadingScreenModule::StartupModule()
{
	if (!IsRunningDedicatedServer())
	{
		UE_LOG(LogBlissLoadingScreen, Verbose, TEXT("BlissLoadingScreen: StartupModule"));
		// Load for cooker reference
		LoadObject<UObject>(nullptr, TEXT(LOADING_SCREEN_PATH));
		LoadObject<UObject>(nullptr, TEXT(SPLASH_SCREEN_PATH));
		if (IsMoviePlayerEnabled())
		{
			UE_LOG(LogBlissLoadingScreen, Verbose, TEXT("BlissLoadingScreen: IsMoviePlayerEnabled"));
			FLoadingScreenAttributes LoadingScreen;
			LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
			LoadingScreen.MinimumLoadingScreenDisplayTime = 5.0f;
			LoadingScreen.WidgetLoadingScreen = SNew(SBlissLoadingScreen).TexturePath(LOADING_SCREEN_PATH);
			GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
		}
	}
}

void IBlissLoadingScreenModule::StartInGameLoadingScreen(const FString& PendingMap, const FString& TexturePath)
{
	if (!IsRunningDedicatedServer())
	{
		UE_LOG(LogBlissLoadingScreen, Verbose, TEXT("BlissLoadingScreen: StartInGameLoadingScreen"));
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
		if (PendingMap.Contains(TEXT("MainMenu_P"), ESearchCase::CaseSensitive))
		{
			LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
			LoadingScreen.WidgetLoadingScreen = SNew(SBlissLoadingScreen).TexturePath(TexturePath);
		}
		else
		{
			LoadingScreen.WidgetLoadingScreen = SNew(SBlissLoadingScreen).TexturePath(TexturePath);
		}

		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}
}

DEFINE_LOG_CATEGORY(LogBlissLoadingScreen);

IMPLEMENT_GAME_MODULE(IBlissLoadingScreenModule, BlissLoadingScreen);
