// Copyright (c) 2025 Guardbrawl Games

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
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

	UFUNCTION(BlueprintImplementableEvent)
	void TriggerTutorialEnd();
};
