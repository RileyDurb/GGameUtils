// Copyright (c) 2025 Guardbrawl Games

#pragma once

#include "CoreMinimal.h"
#include "TutorialInfoSetter.h"
#include "GameplayTagContainer.h" // For having gameplay tag vriables
#include "NativeGameplayTags.h" // For defining the example gameplay tags
#include "BPI_TutorialTransitions.h"
#include "Blueprint/UserWidget.h"
#include "InfoSetter_Transitions.generated.h"


// Open transition tag declarations
UE_DECLARE_GAMEPLAY_TAG_EXTERN(GGameUtils_TutorialOpenTransitions_FromLeft);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(GGameUtils_TutorialOpenTransitions_FadeIn);

// Close transition tag declarations
UE_DECLARE_GAMEPLAY_TAG_EXTERN(GGameUtils_TutorialCloseTransitions_ToLeft);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(GGameUtils_TutorialCloseTransitions_FadeOut);



/**
 * 
 */
UCLASS(Blueprintable)
class EXAMPLES_API UInfoSetter_Transitions : public UTutorialInfoSetter
{
	GENERATED_BODY()

public:
	void SetInfoFromExposedVariables_Implementation(UUserWidget* spawnedWidget) override
	{
		if (spawnedWidget->GetClass()->ImplementsInterface(UBPI_TutorialTransitions::StaticClass())) // If the widget implements the transition setting interface
		{
			IBPI_TutorialTransitions::Execute_SetTutorialTransitions(spawnedWidget, mOpenTransitionTag, mCloseTransitionTag); // Pass in the gameplay tags to pick the transitions to use
		}
	}

private:
	UPROPERTY(EditAnywhere)
	FGameplayTag mOpenTransitionTag;

	UPROPERTY(EditAnywhere)
	FGameplayTag mCloseTransitionTag;
};
