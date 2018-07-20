// Copyright 2018, Colby Hall. All Rights Reserved.

#include "IFirearm.h"
#include "DrawDebugHelpers.h"

bool FFirearmAttributes::HasFireMode(EFireMode FireMode) const
{
	const uint32 Mask = 0x1 << int32(FireMode);

	return (FireModesMask & Mask) != 0;
}

AIFirearm::AIFirearm(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Description.ItemType = EItemType::Firearm;
	Attributes.FireModesMask = (int32)EFireMode::Semi;
}

void AIFirearm::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AIFirearm, FireMode);
}


bool AIFirearm::CanFire() const
{
	if (FireMode == EFireMode::Burst && ShotsFired >= GetAttributes().BurstCount) return false;

	const float ShotTimeDiff = GetWorld()->GetTimeSeconds() - LastShotFired;
	// if (ShotTimeDiff < 60.f / GetAttributes().RPM) return false;

	return true;
}

void AIFirearm::FireRound()
{
	if (!CanFire())
	{
		StopFiring();
		return;
	}

	const bool bIsInFirstPerson = GetCameraView() == ECameraView::FirstPerson;

	USkeletalMeshComponent* MeshToFireFrom = bIsInFirstPerson ? GetFirstPersonMesh() : GetThirdPersonMesh();
	if (!MeshToFireFrom)
	{
		UE_LOG(LogBliss, Error, TEXT("%s had no mesh to fire from and is in %s"), *GetName(), *FString(bIsInFirstPerson ? "First Person" : "Third Person"));
		return;
	}

	FHitResult HitResult;
	const FVector TraceStart	= MeshToFireFrom->GetSocketLocation(MUZZLE_SOCKET);
	const FVector TraceEnd		= MeshToFireFrom->GetSocketRotation(MUZZLE_SOCKET).Vector() * 1000.f + TraceStart;
	const bool bHit				= GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility);

	if (bHit)
	{
		DrawDebugLine(GetWorld(), TraceStart, HitResult.ImpactPoint, FColor::Black, false, 5.f, 0, 2.f);
	}
	else
	{
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Black, false, 5.f, 0, 2.f);
	}

	ShotsFired++;
	LastShotFired = GetWorld()->GetTimeSeconds();
}

void AIFirearm::StartFiring_Implementation()
{
	if (GetCharacterChecked()->IsLocallyControlled() && !HasAuthority())
	{
		ServerStartFiring();
	}
	else if (!HasAuthority())
	{
		// @NOTE: Simualted Proxies should never call this
		checkNoEntry();
		return;
	}

	if (!CanFire()) return;

	ShotsFired = 0;
	if (FireMode == EFireMode::Auto || FireMode == EFireMode::Burst)
	{
		GetWorldTimerManager().SetTimer(FiringHandle, this, &AIFirearm::FireRound, 60.f / GetAttributes().RPM, true);
	}
	FireRound();

}

void AIFirearm::StopFiring_Implementation()
{
	if (GetCharacterChecked()->IsLocallyControlled() && !HasAuthority())
	{
		ServerStopFiring();
	}
	else if (!HasAuthority())
	{
		// @NOTE: Simualted Proxies should never call this
		checkNoEntry();
		return;
	}

	if (FireMode == EFireMode::Burst && ShotsFired < GetAttributes().BurstCount) return;
	GetWorldTimerManager().ClearTimer(FiringHandle);
}

void AIFirearm::ServerStartFiring_Implementation()
{
	StartFiring();
}

bool AIFirearm::ServerStartFiring_Validate()
{
	return true;
}

void AIFirearm::ServerStopFiring_Implementation()
{
	StopFiring();
}

bool AIFirearm::ServerStopFiring_Validate()
{
	return true;
}

void AIFirearm::OnRep_FireMode()
{
	if (IsNetMode(NM_DedicatedServer)) return;

	// @TODO: Play animation and sound
}