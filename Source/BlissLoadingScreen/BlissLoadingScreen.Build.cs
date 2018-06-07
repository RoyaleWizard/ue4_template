
using UnrealBuildTool;

// This module must be loaded "PreLoadingScreen" in the .uproject file, otherwise it will not hook in time!

public class BlissLoadingScreen : ModuleRules
{
    public BlissLoadingScreen(ReadOnlyTargetRules Target) : base (Target)
	{
		PrivateIncludePaths.Add("BlissLoadingScreen");
        PublicIncludePaths.Add("BlissLoadingScreen");

        PrivateDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "Slate",
            "MoviePlayer",
            "SlateCore"
        });

        bFasterWithoutUnity = true;
	}
}
