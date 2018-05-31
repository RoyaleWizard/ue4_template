// Copyright 2018, Colby Hall. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class BlissTarget : TargetRules
{
	public BlissTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Bliss" } );
	}
}
