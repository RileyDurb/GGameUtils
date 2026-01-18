// Copyright (c) 2025 Guardbrawl Games

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayTagContainer.h"

#include "TutorialSaveGame.h" // Tutorial save game, and completion info struct
#include "TutorialSaveGameInstance.generated.h"

/**
 * Class responsible for saving/ allowing access to the tutorial save data
 */


UCLASS()
class GGAMEUTILSTUTORIALSYSTEM_API UTutorialSaveGameInstance : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Tutorial Completion Tracking")
	int GetNumTutorialCompletions(FGameplayTag tutorialToCheck);

	UFUNCTION(BlueprintCallable, Category="Tutorial Completion Tracking")
	void MarkTutorialCompletion(FGameplayTag completedTutorialTag, bool addToFilePersitingSaves);

	UFUNCTION(BlueprintCallable, Category="Saving")
	void SaveSaveableTutorialStates();

	UFUNCTION(BlueprintCallable, Category = "Saving")
	void ResetTutorialSaveStatesAndSave();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

protected:

	UPROPERTY(EditAnywhere)
	FString mDefaultSaveGameName = "Tutorial_Default";

	// Make this editable just in case the game wants different user indexes on the same platform
	// By default, only uses the 1st slot for all
	UPROPERTY(EditAnywhere, blueprintReadWrite)
	int mPlatformUserSlot = 0;

	// Probably should make this a configuration file, but by default, disables saving in the editor so you can keep testing tutorials, and enables saving in builds
#if WITH_EDITOR
	bool mDebugAlwaysResetSave = false;
#else
	bool mDebugAlwaysResetSave = false;
#endif



private:
	TMap<FGameplayTag, FTutorialCompletionInfo> mTutorialCompletions;
	TMap<FGameplayTag, FTutorialCompletionInfo> mSessionOnlyTutorialCompletions;

	UTutorialSaveGame* mTutorialSaveGame;
};
