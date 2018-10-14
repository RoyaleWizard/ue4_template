// Copyright 2018, Colby Hall. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ICharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class BLISS_API UICharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	UICharacterMovementComponent();

	UPROPERTY(Category = "Character Movement: Walking", EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", UIMin = "0"))
	float StrafeMultiplier;

	UPROPERTY(Category = "Character Movement: Walking", EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", UIMin = "0"))
	float BackPedalMultiplier;

	//BEGIN UMovementComponent Interface
	virtual float GetMaxSpeed() const override;
	//END UMovementComponent Interface

	
	
};
