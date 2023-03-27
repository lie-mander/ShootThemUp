// Shoot Them Up Game. All Rights Reserved

using UnrealBuildTool;
using System.Collections.Generic;

public class ShootThemUpServerTarget : TargetRules
{
	public ShootThemUpServerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ShootThemUp" } );
	}
}
