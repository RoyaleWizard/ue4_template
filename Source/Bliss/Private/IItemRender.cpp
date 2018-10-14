// Copyright 2018, Colby Hall. All Rights Reserved.

#include "IItemRender.h"

FName AIItemRender::ItemMeshComponentName(TEXT("Item Mesh"));
FName AIItemRender::Capture2DComponentName(TEXT("Capture 2D"));
FName AIItemRender::CameraComponentName(TEXT("Camera"));

AIItemRender::AIItemRender(const FObjectInitializer& ObjectInitializer)
{
	ItemMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, AIItemRender::ItemMeshComponentName);
	SetRootComponent(ItemMesh);


	Camera = CreateDefaultSubobject<UCameraComponent>(AIItemRender::CameraComponentName);
	Camera->SetRelativeLocationAndRotation(FVector(0.f, 220.f, 90.f), FRotator(0.f, 0.f, -90.f));
	Camera->SetupAttachment(RootComponent);

	Capture2D = ObjectInitializer.CreateDefaultSubobject<USceneCaptureComponent2D>(this, AIItemRender::Capture2DComponentName);
	Capture2D->SetupAttachment(Camera);
	Capture2D->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;
}

void AIItemRender::BeginPlay()
{
	Super::BeginPlay();

	Capture2D->ShowOnlyComponent(GetItemMesh());
}

