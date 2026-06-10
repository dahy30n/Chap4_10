// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Chap4_10 : ModuleRules
{
	public Chap4_10(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "Slate", "SlateCore" });
	}
}
