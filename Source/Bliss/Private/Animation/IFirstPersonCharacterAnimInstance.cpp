// Copyright 2018, Colby Hall. All Rights Reserved.

#include "IFirstPersonCharacterAnimInstance.h"
#include "Items/IEquippableItem.h"
#include "Player/ICharacter.h"
#include "DrawDebugHelpers.h"


void UIFirstPersonCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!OwningCharacter) return;

	AIEquippableItem* CurrentEquippable = OwningCharacter->GetCurrentEquippable();

}

