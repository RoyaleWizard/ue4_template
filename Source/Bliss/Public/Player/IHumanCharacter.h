// Copyright 2018, Colby Hall. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/ICharacter.h"
#include "IHumanCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BLISS_API AIHumanCharacter : public AICharacter
{
	GENERATED_BODY()
	
public:

	AIHumanCharacter(const FObjectInitializer& ObjectInitializer);
	
private:

	/** Third Person Head Mesh*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* ThirdPersonHeadMesh;

public:


	FORCEINLINE class USkeletalMeshComponent* GetThirdPersonHeadMesh() const { return ThirdPersonHeadMesh; }

	/** Name of the First Person Mesh*/
	static FName ThirdPersonHeadMeshComponentName;

public:

	virtual void SetCameraView(const ECameraView NewCameraView) override;
	
};
