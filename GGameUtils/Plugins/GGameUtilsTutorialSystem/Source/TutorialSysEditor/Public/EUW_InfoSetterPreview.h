// Copyright (c) 2025 Guardbrawl Games

#pragma once
#include "CoreMinimal.h"

//#ifndef WITH_EDITOR
#include "EditorUtilityWidget.h"
#include "BaseTutorialConditions.h"
#include "Components/CanvasPanel.h"
#include "Blueprint/UserWidget.h"

#include "EUW_InfoSetterPreview.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class TUTORIALSYSEDITOR_API UEUW_InfoSetterPreview : public UEditorUtilityWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintImplementableEvent, Category="Interface", meta = (ForceAsFunction))
	void InitializePreviewWidgetFromTutorialConditions(UBaseTutorialConditions* tutorialConditionsToUse);

protected:

};

//#endif