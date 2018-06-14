// Copyright 2018, Colby Hall. All Rights Reserved.

#pragma once

#include "Core.h"

#include "Engine.h"
#include "UnrealNetwork.h"

#include "Animation/AnimInstance.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimMontage.h"

#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"


#define print_full(message, time, color) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, time, color, message)
#define print_time(message, time) print_full(message, time, FColor::Black)
#define print(message) print_time(message, 5.f)

DECLARE_LOG_CATEGORY_EXTERN(LogBliss, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogBlissHUD, Warning, All);
DECLARE_LOG_CATEGORY_EXTERN(LogBlissEquippable, Log, All);


/*
DECLARE_LOG_CATEGORY_EXTERN(LogBE, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogIONTrace, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogVivox, Warning, All);
DECLARE_LOG_CATEGORY_EXTERN(LogMM, Warning, All);
DECLARE_LOG_CATEGORY_EXTERN(LogIONWeapons, Warning, All);
*/