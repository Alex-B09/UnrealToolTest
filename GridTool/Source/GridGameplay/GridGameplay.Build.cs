// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GridGameplay : ModuleRules
{
	public GridGameplay(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });
    }
}
