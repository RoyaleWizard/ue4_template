// Copyright 2018, Colby Hall. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ILobbyMap.generated.h"

class UIGameInstance;

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EZoneEnum : uint8
{
	ZE_White 	UMETA(DisplayName = "White"),
	ZE_Green 	UMETA(DisplayName = "Green"),
	VE_Red		UMETA(DisplayName = "Red"),
	VE_Yellow	UMETA(DisplayName = "Yellow")

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
	class UButton* Button_White;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Green;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Red;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Yellow;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlayerCount_White;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlayerCount_Green;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlayerCount_Red;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlayerCount_Yellow;

	UFUNCTION()
	void WhiteSelected();

	UFUNCTION()
	void GreenSelected();

	UFUNCTION()
	void RedSelected();

	UFUNCTION()
	void YellowSelected();

	UFUNCTION()
	void ResetWhiteSelection();

	UFUNCTION()
	void ResetGreenSelection();

	UFUNCTION()
	void ResetRedSelection();

	UFUNCTION()
	void ResetYellowSelection();

	bool WhiteFlag = false;
	bool GreenFlag = false;
	bool RedFlag = false;
	bool YellowFlag = false;

	UIGameInstance* IGI;

	UFUNCTION()
	void UpdateZonePlayerCount(const FString PlayerCount, const EZoneEnum ZoneName);

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
	EVictoryEnum VictoryEnum;*/
};
