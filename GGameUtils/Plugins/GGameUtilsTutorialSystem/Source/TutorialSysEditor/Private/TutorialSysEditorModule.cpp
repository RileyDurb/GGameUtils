// Copyright (c) 2026 Guardbrawl Games

#include "TutorialSysEditor.h"



#include "BaseTutorialConditionsEditor.h" // Include tutorial condition class we're customizing the details of

IMPLEMENT_MODULE(FTutorialSysEditorModule, TutorialSysEditor);

void FTutorialSysEditorModule::StartupModule()
{
//#ifndef WITH_EDITOR
	//UE_LOG(LogTemp, Warning, TEXT("TutorialSysEditor Module loaded"));
	FPropertyEditorModule& propertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	propertyModule.RegisterCustomClassLayout("BaseTutorialConditions", FOnGetDetailCustomizationInstance::CreateStatic(&FBaseTutorialConditionsEditor::MakeInstance));
//#endif
}

void FTutorialSysEditorModule::ShutdownModule()
{
	//UE_LOG(LogTemp, Warning, TEXT("TutorialSysEditor Module unloaded"));

	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}


