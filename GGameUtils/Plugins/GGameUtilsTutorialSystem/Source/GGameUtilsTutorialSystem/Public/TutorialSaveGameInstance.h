// Copyright (c) 2025 Guardbrawl Games

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayTagContainer.h"

#include "TutorialSaveGameInstance.generated.h"

/**
 * 
 */
USTRUCT()
struct GGAMEUTILSTUTORIALSYSTEM_API FTutorialCompletionInfo
{
	GENERATED_USTRUCT_BODY()

public:
	int numCompletions = 0;
};

UCLASS()
class GGAMEUTILSTUTORIALSYSTEM_API UTutorialSaveGameInstance : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Tutorial Completion Tracking")
	int GetTutorialCanTrigger(FGameplayTag tutorialToCheck);

	UFUNCTION(BlueprintCallable, Category="Tutorial Completion Tracking")
	void MarkTutorialCompletion(FGameplayTag completedTutorialTag);

private:

	TMap<FGameplayTag, FTutorialCompletionInfo> mTutorialCompletions;
};
