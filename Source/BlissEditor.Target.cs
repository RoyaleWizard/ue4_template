// Copyright 2018, Colby Hall. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class BlissEditorTarget : TargetRules
{
	public BlissEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "Bliss" } );
	}
}
