// Copyright (c) 2025 Guardbrawl Games

#include "TutorialMonitor.h"

#include "GameFramework/Pawn.h"


// Sets default values for this component's properties
UTutorialMonitor::UTutorialMonitor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTutorialMonitor::BeginPlay()
{
	Super::BeginPlay();

	// ...

	mInitTimestamp = GetWorld()->GetRealTimeSeconds();

	for (auto it = mTutorialDefinitions->mTutorials.begin(); it != mTutorialDefinitions->mTutorials.end(); ++it)
	{
		// If we have a valid tutorial set for this tutorial
		if (mTutorialDefinitions->mTutorials[it->Key] != NULL)
		{
			mCreatedTutorials.Add(it->Key, NewObject<UBaseTutorialConditions>(this, mTutorialDefinitions->mTutorials[it->Key])); // Creates a tutorial of the specificed tutorial type

			mCreatedTutorials[it->Key]->SetInitTimestamp(mInitTimestamp);
		}
	}
}


// Called every frame
void UTutorialMonitor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	APlayerController* playerController = GetPlayerControllerForTutorial();

	if (playerController == nullptr)
	{
		ENetMode currNetMode = GetNetMode();
		UE_LOG(LogTemp, Warning, TEXT("TutorialMonitor:TickComponent: Owner does not have a valid player controller at this time. NetMode: %i"), currNetMode);
		return;
	}
	APawn* owningPawn = playerController->GetPawn();

	// Ensure owner is a pawn
	if (owningPawn == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("TutorialMonitor:TickComponent: Owner is not a pawn, make sure it's attached to a pawn, or override the get owning player controller function"));
		return;
	}
	else // Ensure this is a locally controlled real player
	{
		// Don't trigger tutorials if not the local player, or if a bot, only want the active client player to trigger them
		// Can adjust this behaviour if we want to trigger some tutorials on the server, but likely best to just do it on the client, since it's mostly just for their benefit. Unless this causes gameplay fairness bugs
		if (!owningPawn->IsLocallyControlled() || owningPawn->IsBotControlled())
		{
			return;
		}
	}

	// Checks all tutorials, and updates the ones that haven't been completed
	for (auto it = mCreatedTutorials.begin(); it != mCreatedTutorials.end(); ++it)
	{
		TObjectPtr<UBaseTutorialConditions> currTutorial = (*it).Value;

		FGameplayTag tutorialTag = (*it).Key;

		// If tutorial not done
		if (currTutorial->IsCompleted() == false)
		{

			// Checks if tutorial is complete
			bool tutorialDone = false;
			if (currTutorial->IsActive() || currTutorial->CancelIfConpletedBeforeTrigger() == true) // Only checks if tutorial is active, or if it's enabled to be cancelled before it starts, like for a delayed hint
			{
				tutorialDone = currTutorial->CheckTutorialComplete(owningPawn); // Check if tutorial is complete now
			}

			// If complete, handle finishing tutorial
			if (tutorialDone == true)
			{

				// If tutorial was activated
				if (currTutorial->IsActive())
				{
					currTutorial->TriggerTutorialEnd(GetPlayerControllerForTutorial()); // Trigger end sequence

					nActiveTutorials.RemoveTag(tutorialTag); // Tracks that this tutorial is no longer active, so other tutorials can be activated
				}
				else // Count as completed before it begins
				{
					currTutorial->SetCompleted(true);
				}
			}
			else
			{
				if (currTutorial->IsActive() == false								// if not already active
				&& 
				(currTutorial->CheckTutorialShouldActivate(owningPawn) == true   // If activation condition is met
				|| currTutorial->WasManuallyTriggered()))						    // Or was manually triggered
				{

					if (nActiveTutorials.IsEmpty() == false) // If there is a currently active tutorial
					{
						continue; // Don't activate, only allow one tutorial at a time for now
						// NOTE: Probably change this to have a bool on tutorials to enable them to cancel other tutorials, or a bool on tutorials to allow them to be cancelled by others. Can also decice if specific tutorials can cancel others
					}

					// If there is wait time left before we should trigger tutorial
					if (GetWorld()->GetRealTimeSeconds() - mInitTimestamp <= currTutorial->FirstTriggerCheckWaitTime())
					{
						continue; // Skip this for now, wait until time has elapsed
					}


					// If reaching here, trigger tutorial
					currTutorial->TriggerTutorialStart(GetPlayerControllerForTutorial());

					nActiveTutorials.AddTag(tutorialTag); // Tracks that this tutorial is active, to manage whether other tutorials can be activated
				}
			}
		}
	}
}

APlayerController* UTutorialMonitor::GetPlayerControllerForTutorial_Implementation()
{
	APawn* ownerPawn = Cast<APawn>(GetOwner());

	// Make sure owner is a pawn, put a debug message and return if not
	if (ownerPawn == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTutorialMonitor:GetPlayerControllerForTutoriall:monitor with owner of class %s was not a pawn. Reccomend overriding this function based on what it is owned by to get the player controller to use to create the tutorial."), *ownerPawn->GetActorNameOrLabel());

		return nullptr;
	}
	return Cast<APlayerController>(ownerPawn->GetController());
}

bool UTutorialMonitor::TryQueueTutorialTrigger(FGameplayTag tutorialToTrigger)
{
	if (mCreatedTutorials.Contains(tutorialToTrigger) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTutorialMonitor:TryQueueTutorialTrigger:tutorial of tag %s does not exist. Check the tutorial definitions data asset in this component"), tutorialToTrigger.GetTagName());
		return false;
	}

	if (mCreatedTutorials[tutorialToTrigger]->WasManuallyTriggered()) // Don't let it trigger multiple times. NOTE: If we want autorial to be triggered more than once, need to implement resetting it
	{
		return false;
	}

	mCreatedTutorials[tutorialToTrigger]->SetManuallyTriggered(true);

	return true;
}

