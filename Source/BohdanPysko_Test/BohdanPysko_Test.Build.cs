// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BohdanPysko_Test : ModuleRules
{
	public BohdanPysko_Test(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "Niagara" });
	}
}
