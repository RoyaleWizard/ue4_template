// Copyright 2018, Colby Hall. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "IBaseCharacterAnimInstance.generated.h"

/**
 * Used for storing handik data
 */
USTRUCT(BlueprintType)
struct FHandIKData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector Location;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Alpha;
};

/**
 * 
 */
UCLASS()
class BLISS_API UIBaseCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:

	/** Owning Character stored for editor purposes*/
	UPROPERTY(Transient, BlueprintReadOnly)
	class AICharacter* OwningCharacter;
	
	/**
	 * Current movement speed of OwningCharacter
	 *
	 * @see OwningCharacter
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Movement)
	float Speed;

	/**
	 * Current movement direction in yaw of OwningCharacter
	 *
	 * @see CalculateDirection
	 * @see OwningCharacter
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Movement)
	float Direction;

	/**
	 * Current Pitch the character is looking at
	 *
	 * @see OwningCharacter
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
	float ViewPitch;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Transform)
	FHandIKData LeftHandIK;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Transform)
	FHandIKData RightHandIK;


public:

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
};
