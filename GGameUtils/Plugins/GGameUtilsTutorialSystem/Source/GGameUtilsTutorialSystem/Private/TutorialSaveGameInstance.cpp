// Copyright (c) 2025 Guardbrawl Games

#include "TutorialSaveGameInstance.h"
#include "Kismet/GameplayStatics.h"


int UTutorialSaveGameInstance::GetTutorialCanTrigger(FGameplayTag tutorialToCheck)
{
	// Lazily add tutorial info for tutorials that haven't been checked for
	if (mTutorialCompletions.Contains(tutorialToCheck) == false)
	{
		mTutorialCompletions.Add(tutorialToCheck, FTutorialCompletionInfo()); // Tutorial not tracked yet, add it's info

		return true; // No completions, so let it be triggered
	}

	// If past max number of completions (to start, just test 1 as the max completions)
	if (mTutorialCompletions[tutorialToCheck].numCompletions > 0)
	{
		return false; // don't allow it to be triggered
	}
	else
	{
		return true; // Allow it to be triggered
	}
}

void UTutorialSaveGameInstance::MarkTutorialCompletion(FGameplayTag completedTutorialTag)
{
	// Lazily add tutorial info for tutorials that haven't been checked for
	if (mTutorialCompletions.Contains(completedTutorialTag) == false)
	{
		mTutorialCompletions.Add(completedTutorialTag, FTutorialCompletionInfo()); // Tutorial not tracked yet, add it's info
	}

	mTutorialCompletions[completedTutorialTag].numCompletions++;
}

void UTutorialSaveGameInstance::SaveSaveableTutorialStates()
{
	if (mDebugAlwaysResetSave == false) // Don't save if debug save cancelling is on
	{
		UTutorialSaveGame* currentSaveGame = Cast<UTutorialSaveGame>(UGameplayStatics::LoadGameFromSlot(mDefaultSaveGameName, mPlatformUserSlot));
		//mTutorialSaveGame->mSavedTutorialStates = mTutorialCompletions;
		currentSaveGame->mSavedTutorialStates = mTutorialCompletions;
		currentSaveGame->testSaveWorking = true;

		// Saves current tutorial states to a file. TODO: make tutorials able to be individully decided whether they should savee, and also make a debug toggle to make nothing save
		UGameplayStatics::SaveGameToSlot(currentSaveGame, mDefaultSaveGameName, mPlatformUserSlot);

		UE_LOG(LogTemp, Warning, TEXT("Finished"));

	}

}

void UTutorialSaveGameInstance::Initialize(FSubsystemCollectionBase& Collection)
{
	// If save game doesn't exist
	if (UGameplayStatics::DoesSaveGameExist(mDefaultSaveGameName, mPlatformUserSlot) == false || mDebugAlwaysResetSave)
	{
		// Create new default save game
		mTutorialSaveGame = Cast<UTutorialSaveGame>(UGameplayStatics::CreateSaveGameObject(UTutorialSaveGame::StaticClass()));
	}
	else // Save game does exist
	{
		// Load existing save game file
		mTutorialSaveGame = Cast<UTutorialSaveGame>(UGameplayStatics::LoadGameFromSlot(mDefaultSaveGameName, mPlatformUserSlot));
	}

	mTutorialCompletions = mTutorialSaveGame->mSavedTutorialStates;

	UE_LOG(LogTemp, Warning, TEXT("Finished"));
}

void UTutorialSaveGameInstance::Deinitialize()
{
	SaveSaveableTutorialStates();
}
