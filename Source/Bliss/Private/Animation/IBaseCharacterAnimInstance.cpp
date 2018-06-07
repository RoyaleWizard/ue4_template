// Copyright 2018, Colby Hall. All Rights Reserved.

#include "IBaseCharacterAnimInstance.h"
#include "Player/ICharacter.h"

void UIBaseCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwningCharacter = Cast<AICharacter>(TryGetPawnOwner());

}

void UIBaseCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{

	// @Note: Everything below this won't be run in editor
	if (!OwningCharacter) return;

	const FVector Velocity = OwningCharacter->GetVelocity();
	const FRotator Rotation = OwningCharacter->GetActorRotation();

	Speed = Velocity.Size();
	Direction = CalculateDirection(Velocity, Rotation);

}

