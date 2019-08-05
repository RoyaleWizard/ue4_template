// Copyright 2018, Colby Hall. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ILobbyMap.generated.h"

#define GETENUMSTRING(etype, evalue) ( (FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true) != nullptr) ? FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true)->GetEnumName((int32)evalue) : FString("Invalid - are you sure enum uses UENUM() macro?") )

class UButton;
class UTextBlock;
class AIPlayerController;
class AIPlayerState;
class AIGameState;

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EZoneEnum : uint8
{
	ZE_NULL		UMETA(DisplayName = "NULL"),
	ZE_White 	UMETA(DisplayName = "White"),
	ZE_Green 	UMETA(DisplayName = "Green"),
	ZE_Red		UMETA(DisplayName = "Red"),
	ZE_Yellow	UMETA(DisplayName = "Yellow")

};


/**
 * 
 */
UCLASS()
class BLISS_API UILobbyMap : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual bool Initialize() override;

	//void OnInitialized();

private:
	UFUNCTION(BlueprintCosmetic)
	void ResetSelectedZoneButtonBGColor(EZoneEnum Zone); // Resets the background color of the selected zone locally

public:
	UPROPERTY(meta = (BindWidget))
	UButton* White_Button;

	UPROPERTY(meta = (BindWidget))
	UButton* Green_Button;

	UPROPERTY(meta = (BindWidget))
	UButton* Red_Button;

	UPROPERTY(meta = (BindWidget))
	UButton* Yellow_Button;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* White_PlayerCount;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Green_PlayerCount;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Red_PlayerCount;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Yellow_PlayerCount;

	UFUNCTION()
	void WhiteZoneSelected();

	UFUNCTION()
	void GreenZoneSelected();

	UFUNCTION()
	void RedZoneSelected();

	UFUNCTION()
	void YellowZoneSelected();

	UFUNCTION()
	void UpdateZonesPlayerCount();

	AIPlayerController* IPC;

	AIPlayerState* IPS;

	AIGameState* IGS;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
	EZoneEnum CurrentSelectedZone = EZoneEnum::ZE_NULL;

	UFUNCTION()
	void SetSelectedZone(const EZoneEnum Zone); // Increments the current selected zone's player count locally

	UFUNCTION()
	void ClearZoneSelection(const EZoneEnum Zone); // Decrements the previous selected zone's player count locally

	UPROPERTY()
	UTextBlock* Zone_PlayerCount;
};
