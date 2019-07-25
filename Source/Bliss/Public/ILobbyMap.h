// Copyright 2018, Colby Hall. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ILobbyMap.generated.h"

#define GETENUMSTRING(etype, evalue) ( (FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true) != nullptr) ? FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true)->GetEnumName((int32)evalue) : FString("Invalid - are you sure enum uses UENUM() macro?") )

class UIGameInstance;
class UButton;
class UTextBlock;

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

public:
	UPROPERTY(meta = (BindWidget))
	UButton* Button_White;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Green;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Red;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Yellow;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerCount_White;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerCount_Green;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerCount_Red;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerCount_Yellow;

	UFUNCTION()
	void WhiteZoneSelected();

	UFUNCTION()
	void GreenZoneSelected();

	UFUNCTION()
	void RedZoneSelected();

	UFUNCTION()
	void YellowZoneSelected();

	UIGameInstance* IGI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
	EZoneEnum CurrentSelectedZone = EZoneEnum::ZE_NULL;

	UFUNCTION()
	void AddToPlayerCount(const EZoneEnum Zone); // Adds to the current selected zone's player count locally

	UFUNCTION()
	void RemoveFromPlayerCount(const EZoneEnum Zone); // Removes from previous selected zone's player count locally


	UPROPERTY()
	UTextBlock* PlayerCount;
};
