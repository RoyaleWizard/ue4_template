// Copyright 2018, Colby Hall. All Rights Reserved.

#include "IBaseCharacterAnimInstance.h"
#include "ICharacter.h"

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

	const FRotator AimRotation = OwningCharacter->IsLocallyControlled() ? OwningCharacter->GetControlRotation() : OwningCharacter->GetBaseAimRotation();

	ViewPitch = FMath::ClampAngle(AimRotation.Pitch * -1.f, -90.f, 90.f);


	Speed = Velocity.Size();
	Direction = CalculateDirection(Velocity, Rotation);

}

