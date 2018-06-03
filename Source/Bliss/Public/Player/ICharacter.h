// Copyright 2018, Colby Hall. All Rights Reserved.

#pragma once

#include "Core.h"
#include "GameFramework/Character.h"
#include "ICharacter.generated.h"

#define CAMERA_SOCKET "FPCamera"
#define TP_ARM_SOCKET "TPCamera"

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

	class UCameraComponent* GetFirstPersonCamera() const;
	class USpringArmComponent* GetThirdPersonArm() const;
	class UCameraComponent* GetThirdPersonCamera() const;
	
	
};
