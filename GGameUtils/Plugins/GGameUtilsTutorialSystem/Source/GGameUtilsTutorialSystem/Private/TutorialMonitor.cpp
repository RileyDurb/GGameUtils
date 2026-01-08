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

	for (int i = 0; i < static_cast<int>(EManagedTutorialTypes::Max); i++)
	{
		// If we have a valid tutorial set for this tutorial
		if (mTutorialDefinitions->mTutorials.Contains(static_cast<EManagedTutorialTypes>(i)) && mTutorialDefinitions->mTutorials[static_cast<EManagedTutorialTypes>(i)] != NULL)
		{
			mCreatedTutorials.Add(static_cast<EManagedTutorialTypes>(i), NewObject<UBaseTutorialConditions>(this, mTutorialDefinitions->mTutorials[static_cast<EManagedTutorialTypes>(i)])); // Creates a tutorial of the specificed tutorial info type
		}
	}
	mInitTimestamp = GetWorld()->GetRealTimeSeconds();
	
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
	for (int i = 0; i < static_cast<int>(EManagedTutorialTypes::Max); i++)
	{
		// If tutorial not done
		if (mCreatedTutorials.Contains(static_cast<EManagedTutorialTypes>(i)) && mCreatedTutorials[static_cast<EManagedTutorialTypes>(i)]->IsCompleted() == false)
		{
			TObjectPtr<UBaseTutorialConditions> currTutorial = mCreatedTutorials[static_cast<EManagedTutorialTypes>(i)];

			// Checks if tutorial is complete
			bool tutorialDone = false;
			if (currTutorial->IsActive() || currTutorial->CancelIfConpletedBeforeTrigger() == true) // Only checks if tutorial is active, or if it's enabled to be cancelled before it starts, like for a delayed hint
			{
				tutorialDone = currTutorial->CheckTutorialComplete(owningPawn); // Check if tutorial is complete now
			}


			if (tutorialDone == true)
			{

				// If tutorial was activated
				if (currTutorial->IsActive())
				{
					currTutorial->TriggerTutorialEnd(GetPlayerControllerForTutorial()); // Trigger end sequence

					nActiveTutorials.Remove(static_cast<EManagedTutorialTypes>(i)); // Tracks that this tutorial is active, so other tutorials can be activated
				}
				else // Count as completed before it begins
				{
					currTutorial->SetCompleted(true);
				}

				continue; // Tutorial done, continue to next tutorial if anybhgyuo
			}
			else
			{
				if (currTutorial->IsActive() == false && currTutorial->CheckTutorialShouldActivate(owningPawn) == true) // If tutorial not already triggered
				{
					if (nActiveTutorials.IsEmpty() == false) // If there is a currently active tutorial
					{
						continue; // Don't activate, only allow one tutorial at a time for now
						// NOTE: Probably change this to have a bool on tutorials to enable them to cancel other tutorials, or a bool on tutorials to allow them to be cancelled by others. Can also decice if specific tutorials can cancel others
					}
					// If time is up to trigger tutorial
					if (GetWorld()->GetRealTimeSeconds() - mInitTimestamp > currTutorial->FirstTriggerCheckWaitTime())
					{
						currTutorial->TriggerTutorialStart(GetPlayerControllerForTutorial());

						nActiveTutorials.Add(static_cast<EManagedTutorialTypes>(i)); // Tracks that this tutorial is active, to manage whether other tutorials can be activated
					}
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

