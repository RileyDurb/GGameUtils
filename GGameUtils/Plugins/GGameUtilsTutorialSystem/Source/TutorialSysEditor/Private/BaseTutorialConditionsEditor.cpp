// Copyright (c) 2025 Guardbrawl Games


#include "BaseTutorialConditionsEditor.h"

#include "Editor/PropertyEditor/Public/DetailLayoutBuilder.h"
#include "Editor/PropertyEditor/Public/DetailCategoryBuilder.h"
#include "Editor/PropertyEditor/Public/DetailWidgetRow.h"
#include "Runtime/Slate/Public/Widgets/Text/STextBlock.h"
#include "Runtime/Slate/Public/Widgets/Input/SButton.h"

#include "BaseTutorialConditions.h"

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
		];
}



#undef LOCTEXT_NAMESPACE