// Copyright (c) 2025 Guardbrawl Games


#include "BaseTutorialConditionsEditor.h"

// For making the button in the details panel
#include "Editor/PropertyEditor/Public/DetailLayoutBuilder.h"
#include "Editor/PropertyEditor/Public/DetailCategoryBuilder.h"
#include "Editor/PropertyEditor/Public/DetailWidgetRow.h"
#include "Runtime/Slate/Public/Widgets/Text/STextBlock.h"
#include "Runtime/Slate/Public/Widgets/Input/SButton.h"

// For opening editor widgets
#include "EditorUtilitySubsystem.h"
#include "EditorUtilityWidgetBlueprint.h"

// For setting up the editor widget
#include "EUW_InfoSetterPreview.h"


#define LOCTEXT_NAMESPACE "BaseTutorialConditionsEditorDetails"


TSharedRef<IDetailCustomization> FBaseTutorialConditionsEditor::MakeInstance()
{
	return MakeShareable(new FBaseTutorialConditionsEditor);
}

void FBaseTutorialConditionsEditor::CustomizeDetails(IDetailLayoutBuilder& detailBuilder)
{
	IDetailCategoryBuilder& category = detailBuilder.EditCategory("Visuals", FText::GetEmpty(), ECategoryPriority::Important);

	UBaseTutorialConditions* tutorialConditions = nullptr;
	TArray<TWeakObjectPtr<UObject>> customizedObjects;
	// gets the selected objects
	detailBuilder.GetObjectsBeingCustomized(customizedObjects);

	// Find object
	for (TWeakObjectPtr<UObject> object : customizedObjects)
	{
		if (object.IsValid())
		{
			tutorialConditions = Cast<UBaseTutorialConditions>(object);
			if (tutorialConditions != nullptr)
			{
				break;
			}
		}
	}

	check(tutorialConditions); // Ensure found tutorial conditions is valid

	category.AddCustomRow(LOCTEXT("RowSearchName", "Magic"))
		.NameContent()
		[
			SNew(STextBlock)
				.Text(LOCTEXT("DetailName", " "))
				.Font(IDetailLayoutBuilder::GetDetailFont())
		]
		.ValueContent()
		[
			SNew(SButton)
				.Text(LOCTEXT("DetailName", "Preview Info Setter Results"))
				.HAlign(HAlign_Center)
				.ToolTipText(LOCTEXT("ButtonTooltip", "Opens up a window that shows what info setters will look like when applied. Make the window fullscreen for most accurate results"))
				.OnClicked_Lambda([this, tutorialConditions]()-> FReply{this->ActivatePreviewEditorWidget(tutorialConditions); return FReply::Handled(); })
		];
}

void FBaseTutorialConditionsEditor::ActivatePreviewEditorWidget(UBaseTutorialConditions* tutorialConditions)
{
	// Load editor utility widget (uses a hardcoded path)

	FString editorUtilityWidgetPath = TEXT("/Game/Tutorial/Blueprints/Utility/EWB_TutorialInfoSetterPreviewer.EWB_TutorialInfoSetterPreviewer");

	UEditorUtilityWidgetBlueprint* editorWidget = Cast<UEditorUtilityWidgetBlueprint>(StaticLoadObject(UEditorUtilityWidgetBlueprint::StaticClass(), nullptr, *editorUtilityWidgetPath));

	// if editor widget was loaded successfully
	if (editorWidget != nullptr)
	{
		UEditorUtilitySubsystem* editorUtilSubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();
		UEditorUtilityWidget* spawnedWidget = editorUtilSubsystem->SpawnAndRegisterTab(editorWidget);

		UEUW_InfoSetterPreview* spawnedWidgetAsUtilClass = Cast<UEUW_InfoSetterPreview>(spawnedWidget);

		// Initialize editor widget to preview how the tutorial widget from the tutorial conditions looks when modified by the info setters
		if (spawnedWidgetAsUtilClass != nullptr)
		{
			spawnedWidgetAsUtilClass->InitializePreviewWidgetFromTutorialConditions(tutorialConditions);
		}
	}
}



#undef LOCTEXT_NAMESPACE