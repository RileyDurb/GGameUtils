using UnrealBuildTool;

// Makes the module visible for unreal
public class Examples : ModuleRules

{

    public Examples(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "GameplayTags", "GGameUtilsTutorialSystem" });
    }

}
