using UnrealBuildTool;

// Makes the module visible for unreal
public class TutorialSysEditor : ModuleRules
{
	public TutorialSysEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"GGameUtilsTutorialSystem"
			});

		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.AddRange(new string[] { "DetailCustomizations", "PropertyEditor", "EditorStyle", "Blutility", "UMGEditor", "UMG"});
			PublicDependencyModuleNames.AddRange(new string[] { "UnrealEd" });
		}
	}

}
