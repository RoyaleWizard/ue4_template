// Copyright 2018, Colby Hall. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IInteractionInterface.generated.h"

USTRUCT(BlueprintType)
struct FInteractionOption
{
	GENERATED_BODY()

public:

	/** Interaction name */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText DisplayText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TAssetPtr<UTexture2D> DisplayImage;

	/** Name of the function to call */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName FunctionName;

	/** Object to call FunctionName on */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UObject* Object;

};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BLISS_API IIInteractionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/**
	 * Gets all possible interactions in an actor
	 *
	 * All functions should return void and pass in an actor pointer as a param
	 * @BlueprintNativeEvent
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void GetInteractionOptions(AActor* EventInstigator, TArray<FInteractionOption>& OutInteractions);
	
	
};
