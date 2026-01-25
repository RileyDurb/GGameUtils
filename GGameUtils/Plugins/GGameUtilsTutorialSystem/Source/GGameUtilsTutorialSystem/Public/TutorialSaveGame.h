// Copyright (c) 2025 Guardbrawl Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"

#include "GameplayTagContainer.h"
#include "TutorialSaveGame.generated.h"


USTRUCT()
struct GGAMEUTILSTUTORIALSYSTEM_API FTutorialCompletionInfo
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, Category="SavedData")
	int numCompletions = 0;
};
/**
 * Brief: Save game for the completion states and any other info for the GGameUtils Tutorial System
 */
UCLASS()
class GGAMEUTILSTUTORIALSYSTEM_API UTutorialSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category="TutorialStates")
	TMap<FGameplayTag, FTutorialCompletionInfo> mSavedTutorialStates;
	
};
