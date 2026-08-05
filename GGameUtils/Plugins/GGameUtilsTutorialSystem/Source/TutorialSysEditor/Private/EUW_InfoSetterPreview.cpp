// Copyright (c) 2025 Guardbrawl Games

#include "EUW_InfoSetterPreview.h"
#include "TutorialInfoSetter.h"


void UEUW_InfoSetterPreview::NativeConstruct()
{
	Super::NativeConstruct();
}


//void UEUW_InfoSetterPreview::InitializePreviewWidgetFromTutorialConditions(UBaseTutorialConditions* tutorialConditionsToUse)
//{
//	UUserWidget* widgetToPreview = CreateWidget(this, tutorialConditionsToUse->mTutorialPopupClass);
//
//	// Ensures created widget is valid
//	if (widgetToPreview == nullptr)
//	{
//		FString tutorialName;
//		tutorialConditionsToUse->GetName(tutorialName);
//		UE_LOG(LogTemp, Warning, TEXT("UEUW_InfoSetterPreview::InitializePreviewWidgetFromTutorialConditions: given tutorial conditions %s did not have a valid popup widget to create"), *tutorialName);
//		return;
//	}
//
//	TArray<UTutorialInfoSetter*> infoSetters = tutorialConditionsToUse->GetInfoSetters();
//
//	// Add to parent
//	ParentPreview->AddChildToCanvas(Cast<UWidget>(widgetToPreview));
//
//	// Apply each info setter (if any)
//	for (int i = 0; i < infoSetters.Num(); i++)
//	{
//		infoSetters[i]->SetInfoFromExposedVariables(widgetToPreview);
//	}
//

//}
