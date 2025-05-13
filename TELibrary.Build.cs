// Copyright Tomorrow Evening, all rights reserved.

using System.IO;
using UnrealBuildTool;

public class TELibrary : ModuleRules {
	public TELibrary(ReadOnlyTargetRules Target) : base(Target) {
		PublicDependencyModuleNames.Add("Core");

		// JSON support
		PublicDependencyModuleNames.Add("Json");
		PublicDependencyModuleNames.Add("JsonUtilities");
		PublicDefinitions.Add("WITH_TELIB_JSON=1");

		// WebSocket support
		bool bHasWebSockets = Directory.Exists(
			Path.Combine(ModuleDirectory, "../../Plugins/Runtime/WebSockets")
		);
		if (bHasWebSockets) PublicDependencyModuleNames.Add("WebSockets");
		PublicDefinitions.Add($"WITH_TELIB_WEBSOCKETS={(bHasWebSockets ? 1 : 0)}");
	}
}
