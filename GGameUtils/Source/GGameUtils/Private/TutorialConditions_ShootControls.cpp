// Copyright (c) 2025 Guardbrawl Games


#include "TutorialConditions_ShootControls.h"

UE_DEFINE_GAMEPLAY_TAG_COMMENT(GGameUtils_Tutorials_CPPShootTutorial, "GGameUtils.Tutorials.CPPShootTutorial", "CPP version of shoot controls tutorial");

#define LOCTEXT_NAMESPACE "TutorialText"

UTutorialConditions_ShootControls::UTutorialConditions_ShootControls()
{
	mUseVisualDataOverride = true;


#define LOCTEXT_NAMESPACE "TutorialText"
	mVisualData.tutorialTextOverride = LOCTEXT("TutorialText", "Press <Italic>Left Click</> to shoot");


}


#undef LOCTEXT_NAMESPACE