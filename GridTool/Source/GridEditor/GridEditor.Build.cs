// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GridEditor : ModuleRules
{
	public GridEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] 
		{
			"Core", 
			"CoreUObject", 
			"Engine",
			"ToolMenus",
			"Slate",
			"SlateCore",
			"UnrealEd",
            "EditorFramework",

            "GridGameplay"
		});
    }
}
