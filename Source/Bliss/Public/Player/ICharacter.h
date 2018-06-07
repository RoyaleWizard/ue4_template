// Copyright 2018, Colby Hall. All Rights Reserved.

#pragma once

#include "Core.h"
#include "GameFramework/Character.h"
#include "ICharacter.generated.h"

#define CAMERA_SOCKET "FPCamera"
#define TP_ARM_SOCKET "TPCamera"

UENUM(BlueprintType)
enum ECameraView
{
	FirstPerson,
	ThirdPerson
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

	/** First Person Character Mesh*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* FirstPersonMesh;

	/** First Person Camera activated when in first person */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCamera;

	/** Arm parent to the Third Person Camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* ThirdPersonArm;

	/** Third Person Camera activated when in third person */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* ThirdPersonCamera;

public:	

	class USkeletalMeshComponent* GetFirstPersonMesh() const;

	/** Name of the First Person Mesh*/
	static FName FirstPersonMeshName;

	class UCameraComponent* GetFirstPersonCamera() const;

	/** Name of the FirstPersonCamera */
	static FName FirstPersonCameraName;

	class USpringArmComponent* GetThirdPersonArm() const;

	/** Name of ThirdPersonSpringArm*/
	static FName ThirdPersonArmName;

	class UCameraComponent* GetThirdPersonCamera() const;
	
	/** Name of ThirdPersonCamera*/
	static FName ThirdPersonCameraName;

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
	
};
