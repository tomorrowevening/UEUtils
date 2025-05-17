// Copyright Tomorrow Evening, all rights reserved.

using System.IO;
using UnrealBuildTool;

public class Apollo : ModuleRules
{
	public Apollo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",           // always
				"CoreUObject",    // UObject, UCLASS, USTRUCT, etc.
				"Engine",         // everything in Runtime/Engine/Public, including Kismet headers
				"Json",           // your JSON support
				"JsonUtilities"
			}
			);

		// Optional WebSockets
		bool bHasWebSockets = Directory.Exists(
				Path.Combine(ModuleDirectory, "../../Plugins/Runtime/WebSockets")
		);
		if (bHasWebSockets) {
			PublicDependencyModuleNames.Add("WebSockets");
		}

		PublicDefinitions.Add("WITH_TELIB_JSON=1");
		PublicDefinitions.Add($"WITH_TELIB_WEBSOCKETS={(bHasWebSockets ? 1 : 0)}");
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
