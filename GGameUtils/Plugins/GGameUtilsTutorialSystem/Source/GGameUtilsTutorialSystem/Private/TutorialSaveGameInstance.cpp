// Copyright (c) 2025 Guardbrawl Games


#include "TutorialSaveGameInstance.h"

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
