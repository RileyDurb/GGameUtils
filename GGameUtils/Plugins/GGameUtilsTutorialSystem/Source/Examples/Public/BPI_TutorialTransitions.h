// Copyright (c) 2025 Guardbrawl Games

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "BPI_TutorialTransitions.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBPI_TutorialTransitions : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class EXAMPLES_API IBPI_TutorialTransitions
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintImplementableEvent, Category="ReusemSetters")
	void SetTutorialTransitions(FGameplayTag openTransitionTag, FGameplayTag closeTransitionTag);
};
