// Copyright 2018, Colby Hall. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/IEquippableItem.h"
#include "IFirearm.generated.h"


UENUM(BlueprintType)
enum class EFirearmType : uint8
{
	Handgun,
	Rifle,
	Shotgun,
	Max
};

USTRUCT(BlueprintType)
struct FFirearmConfig
{
	GENERATED_BODY();

public:


};

/**
 * 
 */
UCLASS()
class BLISS_API AIFirearm : public AIEquippableItem
{
	GENERATED_BODY()
	
public:
	
	AIFirearm(const FObjectInitializer& ObjectInitializer);

};
