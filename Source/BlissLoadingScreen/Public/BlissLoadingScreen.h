
#pragma once

#include "ModuleInterface.h"
#include "SlateBasics.h"

#define LOADING_SCREEN_PATH "/Game/Bliss/UI/Textures/T_LoadingScreen.T_LoadingScreen"
#define SPLASH_SCREEN_PATH "/Game/Bliss/UI/Textures/T_LoadingScreen.T_LoadingScreen"

struct FBlissLoadingScreenBrush : public FSlateDynamicImageBrush, public FGCObject
{
	FBlissLoadingScreenBrush(const FName InTextureName, const FVector2D& InImageSize)
		: FSlateDynamicImageBrush(InTextureName, InImageSize)
	{
		ResourceObject = LoadObject<UObject>(nullptr, *InTextureName.ToString());
	}

	virtual void AddReferencedObjects(FReferenceCollector& Collector)
	{
		if (ResourceObject)
		{
			Collector.AddReferencedObject(ResourceObject);
		}
	}
};

class BLISSLOADINGSCREEN_API SBlissLoadingScreen : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SBlissLoadingScreen)
		: _TexturePath(LOADING_SCREEN_PATH)
	{}
	SLATE_ARGUMENT(FString, TexturePath)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

protected:

	FString TexturePath;

private:

	/** loading screen image brush */
	TSharedPtr<FSlateDynamicImageBrush> LoadingScreenBrush;
};

/** Module interface for this game's loading screens */
class IBlissLoadingScreenModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;

	virtual bool IsGameModule() const override { return true; }

	virtual void StartInGameLoadingScreen(const FString& PendingMap, const FString& TexturePath);
};

DECLARE_LOG_CATEGORY_EXTERN(LogBlissLoadingScreen, Log, All);
