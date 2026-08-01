// Copyright (c) 2025 Guardbrawl Games

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "BaseTutorialConditions.h"
#include "Components/Overlay.h"
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
	void InitializePreviewWidgetFromTutorialConditions(UBaseTutorialConditions* tutorialConditionsToUse);

protected:
	UPROPERTY(meta = (BindWidget))
	UOverlay* ParentOverlay;

};
