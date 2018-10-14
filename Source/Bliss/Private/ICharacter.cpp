// Copyright 2018, Colby Hall. All Rights Reserved.

#include "ICharacter.h"
#include "Bliss.h"
#include "ICharacterMovementComponent.h"
#include "ICharacterInventoryComponent.h"
#include "IInteractionInterface.h"
#include "IEquippableItem.h"
#include "IBlissFunctionLibrary.h"
#include "Components/TimelineComponent.h"
#include "IPlayerController.h"
#include "IPlayerHUD.h"
#include "IItemRender.h"

void FInventoryItem::PostReplicatedAdd(const struct FInventoryArray& InArraySerializer)
{
	Item->SetOwner(InArraySerializer.OwningCharacter);
	Item->OnPickedUp();
}

void FInventoryArray::Add(AIItem* Item)
{
	ensure(OwningCharacter->HasAuthority());
    
	FInventoryItem InventoryItem;
	InventoryItem.Item = Item;
	Array.Add(InventoryItem);
	MarkItemDirty(InventoryItem);
}

bool FInventoryArray::Remove(class AIItem* Item)
{
	ensure(OwningCharacter->HasAuthority());
    
	for (int32 i = 0; i < Array.Num(); i++)
	{
		if (Array[i].Item == Item)
		{
			Array.RemoveAt(i);
			return true;
		}
	}
    
	return false;
}

bool FInventoryArray::Contains(const AIItem* Item)
{
	return false;
}

TArray<AIItem*> FInventoryArray::GetArrayAsItems() const
{
	TArray<AIItem*> Result;
	Result.Reserve(Array.Num());
    
	for (auto It : Array)
	{
		Result.Add(It.Item);
	}
    
	return Result;
}

FName AICharacter::FirstPersonMeshComponentName(TEXT("First Person Mesh"));
FName AICharacter::ThirdPersonMeshComponentName(TEXT("Third Person Mesh"));
FName AICharacter::FirstPersonCameraComponentName(TEXT("First Person Camera"));
FName AICharacter::ThirdPersonArmComponentName(TEXT("Third Person Arm"));
FName AICharacter::ThirdPersonCameraComponentName(TEXT("Third Person Camera"));
FName AICharacter::InventoryComponentName(TEXT("Inventory Component"));

AICharacter::AICharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer.SetDefaultSubobjectClass<UICharacterMovementComponent>(ACharacter::CharacterMovementComponentName).DoNotCreateDefaultSubobject(ACharacter::MeshComponentName))
{
	PrimaryActorTick.bCanEverTick = true;
    
	ThirdPersonMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, AICharacter::ThirdPersonMeshComponentName);
	ThirdPersonMesh->SetupAttachment(RootComponent);
    
	FirstPersonMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, AICharacter::FirstPersonMeshComponentName);
	FirstPersonMesh->SetupAttachment(GetThirdPersonMesh());
	FirstPersonMesh->CastShadow = false;
	FirstPersonMesh->bOnlyOwnerSee = true;
    
	FirstPersonCamera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, AICharacter::FirstPersonCameraComponentName);
	// This is attached to the root component as its easier to setup the camera
	FirstPersonCamera->SetupAttachment(RootComponent, FP_CAMERA_SOCKET);
	FirstPersonCamera->bUsePawnControlRotation = false;
    
	ThirdPersonArm = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, AICharacter::ThirdPersonArmComponentName);
	ThirdPersonArm->SetupAttachment(GetCapsuleComponent(), TP_ARM_SOCKET);
	ThirdPersonArm->bUsePawnControlRotation = true;
    
	ThirdPersonCamera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, AICharacter::ThirdPersonCameraComponentName);
	ThirdPersonCamera->SetupAttachment(GetThirdPersonArm(), USpringArmComponent::SocketName);
    
	InventoryComponent = ObjectInitializer.CreateDefaultSubobject<UICharacterInventoryComponent>(this, AICharacter::InventoryComponentName);
	// @NOTE: This is used in the inventory fast array
	Inventory.OwningCharacter = this;
    
	bUseControllerRotationYaw = true;
    
	NetUpdateFrequency = 60.f;
	InteractionDistance = 400.f;
	AimInterp = 10.f;


	bFiring = false;
	bAiming = false;
}

void AICharacter::BeginPlay()
{
	Super::BeginPlay();
    
	// @TODO: Store last saved camera view and use that one on play
	if (!IsNetMode(NM_DedicatedServer))
	{
		SetCameraView(ECameraView::ThirdPerson);

		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::SnapToTarget, true);
		GetFirstPersonCamera()->AttachToComponent(GetFirstPersonMesh(), AttachmentRules, FP_CAMERA_SOCKET);
	}

	if (!IsLocallyControlled())
	{
		GetFirstPersonMesh()->SetComponentTickEnabled(false);
	}

	if (IsLocallyControlled())
	{
		for (int i = 0; i < 3; i++)
		{

		}
	}
    
}

float AICharacter::GetInputScale() const
{
	return 1.f;
}

void AICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
	if (!IsLocallyControlled()) return;
    
	for (auto Item : GetInventoryArray())
	{
		if (Item)
		{
			print_time(Item->GetName(), DeltaTime);
		}
	}

	if (IsNetMode(NM_DedicatedServer)) return;

	if (bAimingDirty)
	{
		if (!IsAiming())
		{
			const FVector CurrentLocation = GetFirstPersonCamera()->GetComponentLocation();
			const FVector TargetLocation = GetFirstPersonMesh()->GetSocketLocation(FP_CAMERA_SOCKET);

			if (CurrentLocation.Equals(TargetLocation))
			{
				bAimingDirty = false;
			}

			GetFirstPersonCamera()->SetWorldLocation(FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, AimInterp));
		}
		else if (CurrentEquippable)
		{
			const FVector CurrentLocation = GetFirstPersonCamera()->GetComponentLocation();
			const FVector TargetLocation = CurrentEquippable->GetFirstPersonMesh()->GetSocketLocation(FIREARM_AIM_SOCKET);

			if (CurrentLocation.Equals(TargetLocation))
			{
				bAimingDirty = false;
			}

			GetFirstPersonCamera()->SetWorldLocation(FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, AimInterp));
		}
	}
    
}

void AICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    
	PlayerInputComponent->BindAxis("MoveForward", this, &AICharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AICharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AICharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AICharacter::LookUp);
    
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AICharacter::OnInteractPressed);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AICharacter::OnFirePressed);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AICharacter::OnFireReleased);
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AICharacter::OnAimPressed);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &AICharacter::OnAimReleased);
    
	PlayerInputComponent->BindAction("SwitchCamera", IE_Pressed, this, &AICharacter::SwitchCamera);

	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &AICharacter::OnInventoryPressed);
	PlayerInputComponent->BindAction("Inventory", IE_Released, this, &AICharacter::OnInventoryReleased);
    
}

void AICharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
	DOREPLIFETIME(AICharacter, Inventory);
	DOREPLIFETIME(AICharacter, QueuedEquippable);
}

void AICharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void AICharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void AICharacter::Turn(float Value)
{
	AddControllerYawInput(Value * GetInputScale());
}

void AICharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value * GetInputScale());
}

void AICharacter::OnInteractPressed()
{
	FVector ViewLocation;
	FRotator ViewRotation;
    
	GetActorEyesViewPoint(ViewLocation, ViewRotation);
    
	const FVector StartLocation = ViewLocation;
	const FVector EndLocation = ViewLocation + (ViewRotation.Vector() * GetInteractionDistance());
    
	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility))
	{
		AActor* HitActor = HitResult.GetActor();
        
		if (!HitActor) return;
        
		TArray<FInteractionOption> OutOptions;
        
		IIInteractionInterface* InteractionInterface = Cast<IIInteractionInterface>(HitActor);
		if (InteractionInterface)
		{
			InteractionInterface->Execute_GetInteractionOptions(HitActor, this, OutOptions);
		}
		else if (HitActor->GetClass()->ImplementsInterface(UIInteractionInterface::StaticClass()))
		{
			IIInteractionInterface::Execute_GetInteractionOptions(HitActor, this, OutOptions);
		}
        
		if (OutOptions.Num() > 0)
		{
			UIBlissFunctionLibrary::CallInteractionFunction(OutOptions[0], this);
		}
	}
    
	UE_LOG(LogBliss, Verbose, TEXT("On Interact Pressed"));
}

void AICharacter::OnFirePressed()
{
	bFiring = true;

	if (CurrentEquippable)
	{
		CurrentEquippable->StartFiring();
		UE_LOG(LogBlissEquippable, Verbose, TEXT("On Fire Pressed with equippable %s"), *CurrentEquippable->GetName());
	}
	UE_LOG(LogBlissEquippable, Verbose, TEXT("On Fire Pressed with no equippable"));
}

void AICharacter::OnFireReleased()
{
	bFiring = false;

	if (CurrentEquippable)
	{
		CurrentEquippable->StopFiring();
		UE_LOG(LogBlissEquippable, Verbose, TEXT("On Fire Released with equippable %s"), *CurrentEquippable->GetName());
	}
	UE_LOG(LogBlissEquippable, Verbose, TEXT("On Fire Released with no equippable"));
}

void AICharacter::OnAimPressed()
{
	bAiming = !bAiming;
	
	bAimingDirty = true;

	if (bAiming)
	{
		if (CurrentEquippable)
		{
			CurrentEquippable->StartAiming();
			UE_LOG(LogBlissEquippable, Verbose, TEXT("On Aim Pressed with equippable %s"), *CurrentEquippable->GetName());
		}
		UE_LOG(LogBlissEquippable, Verbose, TEXT("On Aim Pressed with no equippable"));
	}
	else
	{
		if (CurrentEquippable)
		{
			CurrentEquippable->StopAiming();
			UE_LOG(LogBlissEquippable, Verbose, TEXT("On Aim Released with equippable %s"), *CurrentEquippable->GetName());
		}
		UE_LOG(LogBlissEquippable, Verbose, TEXT("On Aim Released with no equippable"));
	}
}

void AICharacter::OnAimReleased()
{
}

void AICharacter::OnInventoryPressed()
{
	AIPlayerController* IPC = Cast<AIPlayerController>(GetController());
	if (IPC)
	{
		AIPlayerHUD* PHUD = Cast<AIPlayerHUD>(IPC->GetHUD());
		if (PHUD)
		{
			IPC->SetInputModeForMenuOpen();
			PHUD->OpenInventory();
		}
	}
}

void AICharacter::OnInventoryReleased()
{
	AIPlayerController* IPC = Cast<AIPlayerController>(GetController());
	if (IPC)
	{
		AIPlayerHUD* PHUD = Cast<AIPlayerHUD>(IPC->GetHUD());
		if (PHUD)
		{
			IPC->SetInputModeForPlaying();
			PHUD->CloseInventory();
		}
	}
}

void AICharacter::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	const ECameraView CurrentView = GetCameraView();
	UCameraComponent* CurrentCamera = (CurrentView == ECameraView::FirstPerson) ? GetFirstPersonCamera() : GetThirdPersonCamera();
	OutLocation = CurrentCamera->GetComponentLocation();
	if (IsLocallyControlled())
	{
		OutRotation = CurrentCamera->GetComponentRotation();
		return;
	}
    
	OutRotation = GetActorRotation();
}

ECameraView AICharacter::GetCameraView() const
{
	if (GetFirstPersonCamera()->IsActive())
	{
		return ECameraView::FirstPerson;
	}
    
	return ECameraView::ThirdPerson;
}

void AICharacter::SetCameraView(const ECameraView NewCameraView)
{
	if (NewCameraView == ECameraView::FirstPerson)
	{
		GetFirstPersonCamera()->Activate();
		GetFirstPersonMesh()->SetOwnerNoSee(false);
		GetThirdPersonCamera()->Deactivate();
		GetThirdPersonMesh()->SetOwnerNoSee(true);
		GetThirdPersonMesh()->bCastHiddenShadow = true;
	}
	else
	{
		GetFirstPersonCamera()->Deactivate();
		GetFirstPersonMesh()->SetOwnerNoSee(true);
		GetThirdPersonCamera()->Activate();
		GetThirdPersonMesh()->SetOwnerNoSee(false);
		GetThirdPersonMesh()->bCastHiddenShadow = false;
	}

	for (AIItem* Item : GetInventoryArray())
	{
		if (IsValid(Item))
		{
			Item->SetCameraView(NewCameraView);
		}
	}
}

void AICharacter::SwitchCamera()
{
	const ECameraView CurrentView = GetCameraView();
    
	if (CurrentView == ECameraView::FirstPerson)
	{
		SetCameraView(ECameraView::ThirdPerson);
	}
	else
	{
		SetCameraView(ECameraView::FirstPerson);
	}
}

TArray<AIItem*> AICharacter::GetInventoryArray() const
{
	return Inventory.GetArrayAsItems();
}

void AICharacter::OnRep_QueuedEquippable()
{
	LocalEquip(QueuedEquippable);
}

void AICharacter::PickupItem(class AIItem* Item)
{
	if (IsLocallyControlled())
	{
		// Do local stuff here
	}
    
	ServerPickupItem(Item);
}

void AICharacter::ServerPickupItem_Implementation(class AIItem* Item)
{
	InventoryComponent->AddItem(Item);
}

bool AICharacter::ServerPickupItem_Validate(class AIItem* Item)
{
	return true;
}

void AICharacter::EquipItem(class AIEquippableItem* Item)
{
	if (!Item)
	{
		return;
	}
    
	if (IsLocallyControlled())
	{
		QueuedEquippable = Item;
		OnRep_QueuedEquippable();
	}
	ServerEquipItem(Item);
    
}

void AICharacter::ServerEquipItem_Implementation(AIEquippableItem* Item)
{
	QueuedEquippable = Item;
	OnRep_QueuedEquippable();
}

bool AICharacter::ServerEquipItem_Validate(AIEquippableItem* Item)
{
	return true;
}

void AICharacter::LocalEquip(AIEquippableItem* Item)
{
	if (!Item)
	{
		return;
	}
    
	CurrentEquippable = Item;
	Item->Equip();
}

bool AICharacter::IsAiming() const
{
	// @NOTE: We can't be aiming if we don't have an item equipped
	if (!CurrentEquippable) return false;

	return bAiming;
}

bool AICharacter::IsFiring() const
{
	return bFiring;
}