// Copyright 2018, Colby Hall. All Rights Reserved.

#include "IPlayerController.h"

#include "IGameInstance.h"
#include "IPlayerCameraManager.h"
#include "IGameState.h"

#define ESCAPE_MENU_Z 9999

AIPlayerController::AIPlayerController()
{
	PlayerCameraManagerClass = AIPlayerCameraManager::StaticClass();

	InputYawScale = 1.f;
	InputPitchScale = 1.f;
	InputRollScale = 1.f;
}

void AIPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UIGameInstance* GameInstance = Cast<UIGameInstance>(GetGameInstance());
	if (GameInstance && IsLocalPlayerController())
	{
		GameInstance->OnEndLoadingScreen();
	}

	EscapeMenuWidget = nullptr;

	IGS = Cast<AIGameState>(GetWorld()->GetGameState());

}

void AIPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("EscapeMenu", IE_Pressed, this, &AIPlayerController::OnEscapeMenuPressed);
}

void AIPlayerController::OnEscapeMenuPressed()
{


	const bool bEscapeMenuOpen = IsEscapeMenuOpen();

	if (bEscapeMenuOpen)
	{
		CloseEscapeMenu();
	}
	else
	{
		OpenEscapeMenu();
	}

}

void AIPlayerController::OpenEscapeMenu()
{
	ensure(!IsNetMode(NM_DedicatedServer));

	if (!EscapeMenuClass)
	{
		UE_LOG(LogBliss, Warning, TEXT("EscapeMenuClass is not set in %s"), *GetClass()->GetName());
		return;
	}

	if (IsEscapeMenuOpen())
	{
		UE_LOG(LogBliss, Verbose, TEXT("%s tried to open an escape menu but one was already open"), *GetName());
	}
	else
	{
		EscapeMenuWidget = CreateWidget<UUserWidget>(this, EscapeMenuClass);
		EscapeMenuWidget->AddToViewport(ESCAPE_MENU_Z);
		SetInputModeForMenuOpen();
	}
}

void AIPlayerController::CloseEscapeMenu()
{
	ensure(!IsNetMode(NM_DedicatedServer));

	if (IsEscapeMenuOpen())
	{
		EscapeMenuWidget->RemoveFromViewport();
		EscapeMenuWidget = nullptr;
		SetInputModeForPlaying();
	}
	else
	{
		UE_LOG(LogBliss, Verbose, TEXT("%s tried to close an escape menu but one was not available to close"), *GetName());
	}
}

void AIPlayerController::SetInputModeForMenuOpen()
{
	FInputModeGameAndUI Mode;
	Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	Mode.SetHideCursorDuringCapture(false);
	bShowMouseCursor = true;
	SetInputMode(Mode);
	
	if (GEngine)
	{
		UGameViewportClient* GameViewport = GEngine->GameViewport;
		if (GameViewport && GameViewport->GetWindow().IsValid() && GameViewport->Viewport)
		{
			FVector2D ViewportSize = FVector2D(GameViewport->Viewport->GetSizeXY());
			ViewportSize /= GameViewport->GetWindow().Get()->GetDPIScaleFactor();
			SetMouseLocation(ViewportSize.X / 2, ViewportSize.Y / 2);
		}
	}

}

void AIPlayerController::SetInputModeForPlaying()
{
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}

void AIPlayerController::ServerIncrementPlayerCount_Implementation(const EZoneEnum Zone)
{
	IGS->IncrementPlayerCount(Zone);
}

bool AIPlayerController::ServerIncrementPlayerCount_Validate(const EZoneEnum Zone)
{
	return true;
}

void AIPlayerController::ServerDecrementPlayerCount_Implementation(const EZoneEnum Zone)
{
	IGS->DecrementPlayerCount(Zone);
}

bool AIPlayerController::ServerDecrementPlayerCount_Validate(const EZoneEnum Zone)
{
	return true;
}