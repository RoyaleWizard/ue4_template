// Copyright 2018, Colby Hall. All Rights Reserved.

#include "IGameMode.h"
#include "ICharacter.h"
#include "IPlayerController.h"
#include "IHUD.h"
#include "IPlayerState.h"
#include "IGameInstance.h"


AIGameMode::AIGameMode()
{
	DefaultPawnClass = AICharacter::StaticClass();
	PlayerControllerClass = AIPlayerController::StaticClass();
	HUDClass = AIHUD::StaticClass();
	PlayerStateClass = AIPlayerState::StaticClass();

}

AActor* AIGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	APlayerStart* FoundPlayerStart = nullptr;

	// Arrays to hold the player starts for each zone
	TArray<APlayerStart*> WhiteZoneStarts;
	TArray<APlayerStart*> GreenZoneStarts;
	TArray<APlayerStart*> RedZoneStarts;
	TArray<APlayerStart*> YellowZoneStarts;
	TArray<APlayerStart*> NullZoneStarts;

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
		APlayerStart* PlayerStart = *It;

		if (PlayerStart->IsA<APlayerStartPIE>())
		{
			// Always prefer the first "Play from Here" PlayerStart, if we find one while in PIE mode
			FoundPlayerStart = PlayerStart;
			break;
		}
		else
		{
			if (PlayerStart->PlayerStartTag == WhiteZoneTag)
			{
				WhiteZoneStarts.Add(PlayerStart);
			}
			else if (PlayerStart->PlayerStartTag == GreenZoneTag)
			{
				GreenZoneStarts.Add(PlayerStart);
			}
			else if (PlayerStart->PlayerStartTag == RedZoneTag)
			{
				RedZoneStarts.Add(PlayerStart);
			}
			else if (PlayerStart->PlayerStartTag == YellowZoneTag)
			{
				YellowZoneStarts.Add(PlayerStart);
			}
			else // Null Tag
			{
				NullZoneStarts.Add(PlayerStart);
			}
		}
		
	}
	
	if (FoundPlayerStart == nullptr)
	{
		UIGameInstance* IGI = Cast<UIGameInstance>(GetGameInstance());
		if (IGI)
		{
			if (WhiteZoneStarts.Num() > 0 && IGI->SelectedZone == EZoneEnum::ZE_White)
			{
				int32 RandIndex = FMath::RandRange(0, WhiteZoneStarts.Num() - 1);
				FoundPlayerStart = WhiteZoneStarts[RandIndex];
				WhiteZoneStarts.RemoveAt(RandIndex);
			}
			else if (GreenZoneStarts.Num() > 0 && IGI->SelectedZone == EZoneEnum::ZE_Green)
			{
				int32 RandIndex = FMath::RandRange(0, GreenZoneStarts.Num() - 1);
				FoundPlayerStart = GreenZoneStarts[RandIndex];
				GreenZoneStarts.RemoveAt(RandIndex);
			}
			else if (RedZoneStarts.Num() > 0 && IGI->SelectedZone == EZoneEnum::ZE_Red)
			{
				int32 RandIndex = FMath::RandRange(0, RedZoneStarts.Num() - 1);
				FoundPlayerStart = RedZoneStarts[RandIndex];
				RedZoneStarts.RemoveAt(RandIndex);
			}
			else if (YellowZoneStarts.Num() > 0 && IGI->SelectedZone == EZoneEnum::ZE_Yellow)
			{
				int32 RandIndex = FMath::RandRange(0, YellowZoneStarts.Num() - 1);
				FoundPlayerStart = YellowZoneStarts[RandIndex];
				YellowZoneStarts.RemoveAt(RandIndex);
			}
			else // FoundPlayerStart = nullptr
			{
				GEngine->AddOnScreenDebugMessage(-1, 40.f, FColor::Emerald, FString::Printf(TEXT("%d"), NullZoneStarts.Num()));
				int32 RandIndex = FMath::RandRange(0, NullZoneStarts.Num() - 1);
				FoundPlayerStart = NullZoneStarts[RandIndex];
				NullZoneStarts.RemoveAt(RandIndex);
				GEngine->AddOnScreenDebugMessage(-1, 40.f, FColor::Emerald, FString::Printf(TEXT("%d"), NullZoneStarts.Num()));
			}	
		}	
	}
	return FoundPlayerStart;
}


