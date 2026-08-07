// Copyright (c) 2026 Guardbrawl Games

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "StructDefinitionsFile.h"
#include "TutorialPopupInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UTutorialPopupInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GGAMEUTILSTUTORIALSYSTEM_API ITutorialPopupInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="EndBehaviour")
	void TriggerTutorialEnd(); // Whatever logic the tutorial needs to remove itself, such as playing an animation, and then removing itself from the viewport

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "StartBehaviour")
	void SetupOnTutorialStart(); // Whatever setup, if any, that is needed for the widget. Called after the info setters are applied and the widget is added to the viewport


	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="ReuseSetters")
	void ApplyVisualDataOverride(FTutorialBasicVisualsData visualDataToUse);
};
