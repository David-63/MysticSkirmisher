// Copyright David-6

using UnrealBuildTool;
using System.Collections.Generic;

public class MysticSkirmisherEditorTarget : TargetRules
{
	public MysticSkirmisherEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "MysticSkirmisher" } );
	}
}
