// Copyright David-6

using UnrealBuildTool;
using System.Collections.Generic;

public class MysticSkirmisherTarget : TargetRules
{
	public MysticSkirmisherTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "MysticSkirmisher" } );
	}
}
