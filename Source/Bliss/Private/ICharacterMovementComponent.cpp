// Copyright 2018, Colby Hall. All Rights Reserved.

#include "ICharacterMovementComponent.h"
#include "Bliss.h"
#include "Engine/NetworkObjectList.h"
#include "ICharacter.h"

UICharacterMovementComponent::UICharacterMovementComponent()
{
	StrafeMultiplier = 0.8f;
	BackPedalMultiplier = 0.1f;
}

float UICharacterMovementComponent::GetMaxSpeed() const
{
	if (MovementMode == MOVE_Walking || MovementMode == MOVE_NavWalking)
	{
		AICharacter* OC = Cast<AICharacter>(GetOwner());
		if (!OC) return 0.f;

		// ECharacterStance CurrentStance = MC->GetStance();
		const float OutSpeed = MaxWalkSpeed;
		const float Angle = OC->GetActorForwardVector() | Velocity.GetSafeNormal();

		if (Angle < 0.7f && Angle > 0.f)
		{
			return OutSpeed * StrafeMultiplier;
		}
		else if (Angle < -0.5f)
		{
			return OutSpeed * BackPedalMultiplier;
		}

		return OutSpeed;
	}

	return Super::GetMaxSpeed();
}
