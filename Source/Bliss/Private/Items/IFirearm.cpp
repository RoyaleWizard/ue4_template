// Copyright 2018, Colby Hall. All Rights Reserved.

#include "IFirearm.h"

AIFirearm::AIFirearm(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ItemDescription.ItemType = EItemType.Firearm;
}
