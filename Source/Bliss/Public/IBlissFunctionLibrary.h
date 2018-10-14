// Copyright 2018, Colby Hall. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "IInteractionInterface.h"
#include "IBlissFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class BLISS_API UIBlissFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	static void CallInteractionFunction(FInteractionOption Option, AActor* EventInstigator);
	
	
};
