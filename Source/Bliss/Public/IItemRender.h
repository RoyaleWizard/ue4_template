// Copyright 2018, Colby Hall. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Camera/CameraComponent.h"
#include "IItemRender.generated.h"

UCLASS()
class BLISS_API AIItemRender : public AActor
{
	GENERATED_BODY()
	
public:	
	AIItemRender(const FObjectInitializer& ObjectInitializer);

private:

	/** Item Mesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* ItemMesh;

	/** Camera Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	/** Capture Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item, meta = (AllowPrivateAccess = "true"))
	class USceneCaptureComponent2D* Capture2D;

public:

	FORCEINLINE class USkeletalMeshComponent* GetItemMesh() const { return ItemMesh; }

	/** Name of the Item Mesh*/
	static FName ItemMeshComponentName;

	FORCEINLINE class UCameraComponent* GetCamera() const { return Camera; }

	/** Name of the Camera Component */
	static FName CameraComponentName;

	FORCEINLINE class USceneCaptureComponent2D* GetCapture2D() const { return Capture2D; }

	/** Name of the Capture Component */
	static FName Capture2DComponentName;

protected:

	virtual void BeginPlay() override;
	
};
