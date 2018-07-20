// Copyright 2018, Colby Hall. All Rights Reserved.

#pragma once

#include "Bliss.h"
#include "Items/IEquippableItem.h"
#include "IFirearm.generated.h"

#define MUZZLE_SOCKET "Muzzle"

UENUM(BlueprintType)
enum class EFirearmType : uint8
{
	Handgun,
	AssaultRifle,
	SMG,
	Shotgun,
	SniperRifle,
	Max
};

UENUM(BlueprintType)
enum class EFireMode : uint8
{
	Semi,
	Burst,
	Auto,
	Lever
};

USTRUCT(BlueprintType)
struct FFirearmAttributes
{
	GENERATED_BODY();

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EFirearmType FirearmType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MagazineCapacity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta = (Bitmask, BitmaskEnum = "EFireMode", DisplayName = "Fire Modes"))
	int32 FireModesMask;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 BurstCount;

	/** How many rounds can be fired per minute*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 RPM;

	bool HasFireMode(EFireMode FireMode) const;

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

protected:

	/**
	 * Details about the firearm that in themselves are const and never change unless attachments are attached
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Item)
	FFirearmAttributes Attributes;

	/**
	 * Current firemode and can also be set in blueprints for the default
	 */
	UPROPERTY(EditDefaultsOnly, ReplicatedUsing = OnRep_FireMode, Category = Item)
	EFireMode FireMode;

	/**
	 * Handle that is used for auto and burst firing
	 */
	UPROPERTY()
	FTimerHandle FiringHandle;

	/**
	 * Count of shots fired from startfiring to stopfiring
	 */
	int8 ShotsFired;

	/**
	 * Time the last round was shot
	 */
	float LastShotFired;


public:

	/** Gets a copy of the attributes of this firearm */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE FFirearmAttributes GetAttributes() const { return Attributes; }

protected:

	virtual bool CanFire() const;

	UFUNCTION()
	virtual void FireRound();

protected:

	/**
	 * Used to start firing on the server
	 */
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerStartFiring();

	/**
	 * Used to stop firing on the server
	 */
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerStopFiring();

	UFUNCTION()
	virtual void OnRep_FireMode();

public:

	virtual void StartFiring_Implementation() override;
	virtual void StopFiring_Implementation() override;
};
