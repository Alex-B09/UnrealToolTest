// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class GridToolEditorTarget : TargetRules
{
	public GridToolEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
		
		ExtraModuleNames.Add("GridTool");
		ExtraModuleNames.Add("GridGameplay");
        ExtraModuleNames.Add("GridEditor");
    }
}
