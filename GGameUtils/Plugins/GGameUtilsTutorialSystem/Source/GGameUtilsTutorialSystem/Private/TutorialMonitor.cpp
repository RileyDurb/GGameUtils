// Copyright (c) 2025 Guardbrawl Games

#include "TutorialMonitor.h"

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

	// Initialize tutorial states by adding a tutorial state for each tutorial, defaulting to unfinished
	for (int i = 0; i < static_cast<int>(EManagedTutorialTypes::Max); i++)
	{
		mTutorialStates.Add(static_cast<EManagedTutorialTypes>(i), false);
	}

	mInitTimestamp = GetWorld()->GetRealTimeSeconds();
	
}


// Called every frame
void UTutorialMonitor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	// TODO: a
	APawn* owningPawn = Cast<APawn>(GetOwner());

	if (owningPawn == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("TutorialMonitor:TickComponent: Owner is not a pawn, make sure it's attached to a pawn instead"));
		return;
	}
	else
	{
		// Don't trigger tutorials if not the local player, or if a bot, only want the active client player to trigger them
		// Can adjust this behaviour if we want to trigger some tutorials on the server, but likely best to just do it on the client, since it's mostly just for their benefit. Unless this causes gameplay fairness bugs
		if (!owningPawn->IsLocallyControlled() || owningPawn->IsBotControlled())
		{
			return;
		}
	}

	for (int i = 0; i < static_cast<int>(EManagedTutorialTypes::Max); i++)
	{
		// If tutorial not done
		if (mTutorialStates[static_cast<EManagedTutorialTypes>(i)] == false)
		{
			
			// Prototying specific case for base moving and aim tutorial
			if (static_cast<EManagedTutorialTypes>(i) == EManagedTutorialTypes::BaseMoveAndAim)
			{
				bool tutorialDone = CheckBaseMoveTutorialComplete(); // Check if tutorial is complete now

				if (tutorialDone == true)
				{
					mTutorialStates[static_cast<EManagedTutorialTypes>(i)] = true;

					// Remove tutorial widget if we spawned it
					if (mSpawnedBaseMovementTutorialWidget != nullptr)
					{
						mSpawnedBaseMovementTutorialWidget->RemoveFromParent(); // TODO: make this call an interface function to trigger the end
						mSpawnedBaseMovementTutorialWidget = nullptr;
					}

					continue; // Tutorial done, contibue to next tutorial if any
				}
				else
				{
					if (mSpawnedBaseMovementTutorialWidget == nullptr) // If tutorial not already triggered
					{
						// If time is up to trigger tutorial
						if (GetWorld()->GetRealTimeSeconds() - mInitTimestamp > mWaitTimeBeforeMovementTutorial)
						{
							mSpawnedBaseMovementTutorialWidget = TriggerBaseMovementTutorial(mBaseMovementTutorialWidgetClass); // Trigger the blueprint implemented tutorial func, so user can override however the tutorial gets added
						}
					}
				}
			}
		}
	}

}

