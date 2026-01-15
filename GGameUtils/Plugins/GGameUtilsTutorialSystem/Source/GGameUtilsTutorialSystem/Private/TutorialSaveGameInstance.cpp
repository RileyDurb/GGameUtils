// Copyright (c) 2025 Guardbrawl Games

#include "TutorialSaveGameInstance.h"
#include "Kismet/GameplayStatics.h"


int UTutorialSaveGameInstance::GetTutorialCanTrigger(FGameplayTag tutorialToCheck)
{
	// Lazily add tutorial info for tutorials that haven't been checked for
	if (mTutorialCompletions.Contains(tutorialToCheck) == false)
	{
		mTutorialCompletions.Add(tutorialToCheck, FTutorialCompletionInfo()); // Tutorial not tracked yet, add it's info
	}

	if (mSessionOnlyTutorialCompletions.Contains(tutorialToCheck) == false)
	{
		mSessionOnlyTutorialCompletions.Add(tutorialToCheck, FTutorialCompletionInfo()); // Tutorial not tracked yet, add it's info
	}


	// If past max number of completions (to start, just test 1 as the max completions)

	int totalTutoralCompletions = 0;

	// If completions only for this session have been tracked, just use those, as that means we don't want to count it's persistent saves
	if (mSessionOnlyTutorialCompletions[tutorialToCheck].numCompletions > 0)
	{
		totalTutoralCompletions = mSessionOnlyTutorialCompletions[tutorialToCheck].numCompletions;
	}
	else // Use the tutorials persistently saved completion count
	{
		totalTutoralCompletions = mTutorialCompletions[tutorialToCheck].numCompletions;
	}

	if (totalTutoralCompletions > 0)
	{
		return false; // don't allow it to be triggered
	}
	else
	{
		return true; // Allow it to be triggered
	}
}

void UTutorialSaveGameInstance::MarkTutorialCompletion(FGameplayTag completedTutorialTag, bool addToFilePersitingSaves)
{
	// Lazily add tutorial info for tutorials that haven't been checked for
	if (mTutorialCompletions.Contains(completedTutorialTag) == false)
	{
		mTutorialCompletions.Add(completedTutorialTag, FTutorialCompletionInfo()); // Tutorial not tracked yet, add it's info
		mSessionOnlyTutorialCompletions.Add(completedTutorialTag, FTutorialCompletionInfo()); // Tutorial not tracked yet, add it's info
	}


	if (addToFilePersitingSaves)
	{
		mTutorialCompletions[completedTutorialTag].numCompletions++;
	}
	else
	{
		mSessionOnlyTutorialCompletions[completedTutorialTag].numCompletions++;
	}
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

void UTutorialSaveGameInstance::ResetTutorialSaveStatesAndSave()
{
	for (auto it = mTutorialCompletions.begin(); it != mTutorialCompletions.end(); ++it)
	{
		it->Value.numCompletions = 0;
	}

	SaveSaveableTutorialStates();
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
