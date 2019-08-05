// Copyright 2018, Colby Hall. All Rights Reserved.

#include "IGameMode.h"

#include "ICharacter.h"
#include "IPlayerController.h"
#include "IHUD.h"
#include "IPlayerState.h"
#include "ILobbyMap.h"
//#include "IPlayerHUD.h"

#define TOO_CLOSE_RADIUS 128

AIGameMode::AIGameMode()
{
	DefaultPawnClass = AICharacter::StaticClass();
	PlayerControllerClass = AIPlayerController::StaticClass();
	HUDClass = AIHUD::StaticClass();
	PlayerStateClass = AIPlayerState::StaticClass();

}

AActor* AIGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	//If PIE, don't do this, so "play from here" works
	if (GetWorld()->WorldType == EWorldType::PIE)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("PIE"));
		return Super::ChoosePlayerStart_Implementation(Player);
	}

	// Arrays to hold the player starts for each zone
	TArray<APlayerStart*> WhiteZoneStarts;
	TArray<APlayerStart*> GreenZoneStarts;
	TArray<APlayerStart*> RedZoneStarts;
	TArray<APlayerStart*> YellowZoneStarts;
	TArray<APlayerStart*> NullZoneStarts;

	WhiteZoneStarts.Reset();
	GreenZoneStarts.Reset();
	RedZoneStarts.Reset();
	YellowZoneStarts.Reset();
	NullZoneStarts.Reset();

	FString WhiteZoneSTag = "White";
	FString GreenZoneSTag = "Green";
	FString RedZoneSTag = "Red";
	FString YellowZoneSTag = "Yellow";

	FName WhiteZoneTag = FName(*WhiteZoneSTag);
	FName GreenZoneTag = FName(*GreenZoneSTag);
	FName RedZoneTag = FName(*RedZoneSTag);
	FName YellowZoneTag = FName(*YellowZoneSTag);

	UWorld* World = GetWorld();
	for (TActorIterator<APlayerStart> It(World); It; ++It)
	{
		APlayerStart* TestPlayerStart = *It;
		if (IsSpawnpointAllowed(TestPlayerStart, Player))
		{
			if (TestPlayerStart->PlayerStartTag == WhiteZoneTag)
			{
				WhiteZoneStarts.Add(TestPlayerStart);
			}
			else if (TestPlayerStart->PlayerStartTag == GreenZoneTag)
			{
				GreenZoneStarts.Add(TestPlayerStart);
			}
			else if (TestPlayerStart->PlayerStartTag == RedZoneTag)
			{
				RedZoneStarts.Add(TestPlayerStart);
			}
			else if (TestPlayerStart->PlayerStartTag == YellowZoneTag)
			{
				YellowZoneStarts.Add(TestPlayerStart);
			}
			else // Null Tag
			{
				NullZoneStarts.Add(TestPlayerStart);
			}
		}
	}
	
	APlayerStart* BestStart = NULL;

	AIPlayerState* IPS = Cast<AIPlayerState>(Player->PlayerState);
	if (IPS)
	{
		if (WhiteZoneStarts.Num() > 0 && IPS->SelectedZone == EZoneEnum::ZE_White)
		{
			BestStart = WhiteZoneStarts[FMath::RandHelper(WhiteZoneStarts.Num())];
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, TEXT("White"));

		}
		else if (GreenZoneStarts.Num() > 0 && IPS->SelectedZone == EZoneEnum::ZE_Green)
		{
			BestStart = GreenZoneStarts[FMath::RandHelper(GreenZoneStarts.Num())];
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, TEXT("Green"));

		}
		else if (RedZoneStarts.Num() > 0 && IPS->SelectedZone == EZoneEnum::ZE_Red)
		{
			BestStart = RedZoneStarts[FMath::RandHelper(RedZoneStarts.Num())];
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, TEXT("Red"));

		}
		else if (YellowZoneStarts.Num() > 0 && IPS->SelectedZone == EZoneEnum::ZE_Yellow)
		{
			BestStart = YellowZoneStarts[FMath::RandHelper(YellowZoneStarts.Num())];
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, TEXT("Yellow"));

		}
		else // FoundPlayerStart = nullptr
		{
			//GEngine->AddOnScreenDebugMessage(-1, 40.f, FColor::Emerald, FString::Printf(TEXT("%d"), NullZoneStarts.Num()));
			BestStart = NullZoneStarts[FMath::RandHelper(NullZoneStarts.Num())];
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, TEXT("NULL"));

		}
	}

	return BestStart;
}

//bool AIGameMode::PlayerCanRestart_Implementation(APlayerController* Player)
//{
//	return true;
//}

bool AIGameMode::IsSpawnpointAllowed(APlayerStart* SpawnPoint, AController* Player) const
{
	if (!SpawnPoint) return false;

	// Character Proximity?
	for (TActorIterator<ACharacter> Itr(GetWorld()); Itr; ++Itr)
	{
		// Check if there's any player within TOO_CLOSE_RADIUS
		if ((SpawnPoint->GetActorLocation() - Itr->GetActorLocation()).SizeSquared() < TOO_CLOSE_RADIUS * TOO_CLOSE_RADIUS)
		{
			return false;
		}

	}
	return true;
}

bool AIGameMode::ShouldSpawnAtStartSpot(AController* Player)
{
	return false;
}

//void AIGameMode::PostLogin(APlayerController* NewPlayer)
//{
//	Super::PostLogin(NewPlayer);
//
//	AIPlayerController* IPC = Cast<AIPlayerController>(NewPlayer);
//	if (IPC)
//	{
//		AIPlayerHUD* IPHUD = Cast<AIPlayerHUD>(IPC->GetHUD());
//		if (IPHUD && IPHUD->MapWidgetInstance)
//			IPHUD->MapWidgetInstance->ClientUpdateZonesPlayerCount();
//	}
//
//}

