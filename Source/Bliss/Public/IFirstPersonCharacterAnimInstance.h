// Copyright 2018, Colby Hall. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IBaseCharacterAnimInstance.h"
#include "IFirstPersonCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BLISS_API UIFirstPersonCharacterAnimInstance : public UIBaseCharacterAnimInstance
{
	GENERATED_BODY()
	
protected:

public:

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	
};
