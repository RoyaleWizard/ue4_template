// Copyright 2018, Colby Hall. All Rights Reserved.

#pragma once

#include "Core.h"
#include "GameFramework/Character.h"
#include "ICharacter.generated.h"

#define FP_CAMERA_SOCKET   "FPCamera"
#define TP_ARM_SOCKET      "TPCamera"
#define FIREARM_AIM_SOCKET "aim"

class AICharacter;

UENUM(BlueprintType)
enum ECameraView
{
	FirstPerson,
	ThirdPerson
};

/**
* Data struct that can be serialized
*
* @see FInventoryArray
*/
USTRUCT()
struct FInventoryItem : public FFastArraySerializerItem
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	class AIItem* Item;

	void PostReplicatedAdd(const struct FInventoryArray& InArraySerializer);
};

/**
* Special array that all InventoryItems
*
* @see FItemIdentifier
*/
USTRUCT()
struct FInventoryArray : public FFastArraySerializer
{
	GENERATED_USTRUCT_BODY()

private:
	/**
	* Actual array used for holding the data
	*
	* @private because we don't want anyone removing items from this
	*/
	UPROPERTY()
	TArray<FInventoryItem> Array;

public:

	/**
	* This is used so we can get a reference to the world
	*
	* @see FItemIdentifier::PostReplicatedAdd
	*/
	UPROPERTY(NotReplicated)
	AICharacter* OwningCharacter;

	void Add(class AIItem* Item);
	bool Remove(class AIItem* Item);
	bool Contains(const class AIItem* Item);
	TArray<AIItem*> GetArrayAsItems() const;

	bool NetDeltaSerialize(FNetDeltaSerializeInfo & DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FInventoryItem, FInventoryArray>(Array, DeltaParms, *this);
	}
};

template<>
struct TStructOpsTypeTraits<FInventoryArray> : public TStructOpsTypeTraitsBase2<FInventoryArray>
{
	enum
	{
		WithNetDeltaSerializer = true,
	};
};

UCLASS()
class BLISS_API AICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	AICharacter(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	 * Gets the scale when scaling input
	 *
	 * @returns scale
	 */
	virtual float GetInputScale() const;

private:

	// Input Functions
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void OnInteractPressed();
	void OnFirePressed();
	void OnFireReleased();
	void OnAimPressed();
	void OnAimReleased();

	void OnInventoryPressed();
	void OnInventoryReleased();

private:

	/** First Person Character Mesh*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* FirstPersonMesh;

	/** Third Person Character Mesh*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* ThirdPersonMesh;

	/** First Person Camera activated when in first person */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCamera;

	/** Arm parent to the Third Person Camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* ThirdPersonArm;

	/** Third Person Camera activated when in third person */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* ThirdPersonCamera;

	/** Inventory Component that manages all inventory functionality */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	class UICharacterInventoryComponent* InventoryComponent;

public:	

	FORCEINLINE class USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMesh; }

	/** Name of the First Person Mesh*/
	static FName FirstPersonMeshComponentName;

	FORCEINLINE class USkeletalMeshComponent* GetThirdPersonMesh() const { return ThirdPersonMesh; }

	/** Name of the Third Person Mesh*/
	static FName ThirdPersonMeshComponentName;

	FORCEINLINE class UCameraComponent* GetFirstPersonCamera() const { return FirstPersonCamera; }

	/** Name of the FirstPersonCamera */
	static FName FirstPersonCameraComponentName;

	FORCEINLINE class USpringArmComponent* GetThirdPersonArm() const { return ThirdPersonArm; }

	/** Name of ThirdPersonSpringArm*/
	static FName ThirdPersonArmComponentName;

	FORCEINLINE class UCameraComponent* GetThirdPersonCamera() const { return ThirdPersonCamera; }
	
	/** Name of ThirdPersonCamera*/
	static FName ThirdPersonCameraComponentName;

	FORCEINLINE class UICharacterInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }

	/** Name of InventoryComponent*/
	static FName InventoryComponentName;

protected:

	UPROPERTY(EditDefaultsOnly, Category = Character)
	float InteractionDistance;

	UPROPERTY(EditDefaultsOnly, Category = Item)
	TSubclassOf<class AIItemRender> ItemRenderClass;

	UPROPERTY()
	TArray<class AIItemRender*> ItemRenderers;

public: 

	virtual void GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const override;

	/**
	 * Get Current Camera View
	 *
	 * @returns Enum
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ECameraView GetCameraView() const;

	/**
	 * Changes active camera and handles mesh changes
	 * 
	 *
	 * @param NewCameraView is the cameraview to set the cameras to
	 * @see GetCameraView
	 * @see SwitchCamera
	 */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	virtual void SetCameraView(const ECameraView NewCameraView);

	/**
	 * Toggles Camera View
	 * 
	 * If First Person then go Third Person
	 * If Third Person then go First Person
	 */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	void SwitchCamera();

	/** Gets the interaction distance of this character */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetInteractionDistance() const { return InteractionDistance; }

protected:

	/**
	 * Currently equipped weapon. Not replicated but changed by QueuedWeapon
	 * 
	 * @see QueuedEquippable
	 */
	UPROPERTY(Transient, BlueprintReadOnly)
	class AIEquippableItem* CurrentEquippable;
	
	/**
	 * Weapon to be equipped
	 *
	 * @see CurrentEquippable
	 * @Replicated
	 */
	UPROPERTY(ReplicatedUsing = OnRep_QueuedEquippable, Transient)
	class AIEquippableItem* QueuedEquippable;

	UFUNCTION()
	virtual void OnRep_QueuedEquippable();

	/**
	 * Actual equip that is called on clients and server
	 *
	 * @protected
	 */
	virtual void LocalEquip(class AIEquippableItem* Item);

public:

	FORCEINLINE AIEquippableItem* GetCurrentEquippable() const { return CurrentEquippable; }

	/**
	 * Inventory Fast Array
	 *
	 * @public for easier access
	 */
	UPROPERTY(Replicated, Transient)
	FInventoryArray Inventory;

	UFUNCTION(BlueprintCallable, Meta=(DisplayName="Get Inventory"))
	TArray<AIItem*> GetInventoryArray() const;

	UFUNCTION(BlueprintCallable)
	void PickupItem(class AIItem* Item);
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerPickupItem(class AIItem* Item);

	/**
	 * Equips whatever item passed in
	 *
	 * Handles server side functions
	 * @see CurrentEquippable
	 * @see QueuedEquippable
	 */
	UFUNCTION(BlueprintCallable)
	virtual void EquipItem(class AIEquippableItem* Item);
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerEquipItem(class AIEquippableItem* Item);

private:

	uint32 bFiring : 1;
	uint32 bAiming : 1;

	/** Used to determine if should interp */
	uint32 bAimingDirty : 1;

public:

	/** Returns true if aiming */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsAiming() const;
	
	/** Returns true if firing */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsFiring() const;

protected:

	/** Speed use when aiming */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
	float AimInterp;

};
