using UnrealBuildTool;

// Makes the module visible for unreal
public class TutorialSysExamples : ModuleRules

{

    public TutorialSysExamples(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "GameplayTags", "UMG", "GGameUtilsTutorialSystem" });
    }

}
