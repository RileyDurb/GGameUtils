// Copyright (c) 2025 Guardbrawl Games

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TutorialInfoSetter.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, EditInlineNew)
class GGAMEUTILSTUTORIALSYSTEM_API UTutorialInfoSetter : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InfoSettingOverrides")
	void SetInfoFromExposedVariables(UUserWidget* spawnedWidget); // Override this in a class derived from the base class to set the tutorial up based on additional variables you want
	virtual void SetInfoFromExposedVariables_Implementation(UUserWidget* spawnedWidget);
	
};
