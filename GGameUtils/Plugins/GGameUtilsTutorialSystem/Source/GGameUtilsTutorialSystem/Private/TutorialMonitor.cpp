// Copyright (c) 2025 Guardbrawl Games

#include "TutorialMonitor.h"
#include "TutorialPopupInterface.h"


#include "GameFramework/Pawn.h"

void UBaseTutorialConditions::TriggerTutorialStart(UTutorialMonitor* monitorToAddTo)
{
	APawn* ownerPawn = Cast<APawn>(monitorToAddTo->GetOwner());

	// Make sure owner is a pawn, put a debug message and return if not
	if (ownerPawn == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UBaseTutorialConditions:TriggerTutorial:monitor with owner of class %s was not a pawn. Reccomend overriding this function to support your own setup."), * monitorToAddTo->GetOwner()->GetActorNameOrLabel());

		return;
	}

	mCreatedTutorialWidget = CreateWidget(ownerPawn->GetLocalViewingPlayerController(), mTutorialPopupClass);

	AddTutorialWidget(monitorToAddTo, mCreatedTutorialWidget); // Handles adding to viewport, letting how the widget is added be overwritten if UI is handled in a particular way

	mIsActive = true;
}

void UBaseTutorialConditions::AddTutorialWidget_Implementation(UTutorialMonitor* monitorToAddTo, UUserWidget* widgetPopup)
{
	APawn* ownerPawn = Cast<APawn>(monitorToAddTo->GetOwner());

	// Make sure owner is a pawn, put a debug message and return if not
	if (ownerPawn == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UBaseTutorialConditions:AddTutorialWidget:monitor with owner of class %s was not a pawn. Reccomend overriding this function to support your own setup."), *monitorToAddTo->GetOwner()->GetActorNameOrLabel());

		return;
	}

	widgetPopup->AddToViewport();
}

void UBaseTutorialConditions::TriggerTutorialEnd(UTutorialMonitor* monitoToAddTo)
{
	// If implements the tutorialpopupinterface, call the tutorial end function
	if (mCreatedTutorialWidget->GetClass()->ImplementsInterface(UTutorialPopupInterface::StaticClass()))
	{
		ITutorialPopupInterface::Execute_TriggerTutorialEnd(mCreatedTutorialWidget); // Calls end interface function
	}
	else
	{
		mCreatedTutorialWidget->RemoveFromParent(); // Just remove from parent. If making this work on more than just widgets, then remove this part, or find a way to make this the base case
	}

	/* Immediately sets is active to false, but may need to delay the setting of false till the the animation of the tutorial end completes
	- One idea is to pass a listener for the widget to call when done
	- another is to make another interface function that gets the time till the end
	*/ 
	mIsActive = false;
}



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

	APawn* owningPawn = Cast<APawn>(GetOwner());

	// Ensure owner is a pawn
	if (owningPawn == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("TutorialMonitor:TickComponent: Owner is not a pawn, make sure it's attached to a pawn instead"));
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
		if (mTutorialStates[static_cast<EManagedTutorialTypes>(i)] == false)
		{

			// Prototying specific case for base moving and aim tutorial
			if (static_cast<EManagedTutorialTypes>(i) == EManagedTutorialTypes::BaseMoveAndAim)
			{
				bool tutorialDone = CheckBaseMoveTutorialComplete(); // Check if tutorial is complete now

				if (tutorialDone == true)
				{
					mTutorialStates[static_cast<EManagedTutorialTypes>(i)] = true;

					// If tutorial was activated
					if (mCreatedTutorials[static_cast<EManagedTutorialTypes>(i)]->IsActive())
					{
						mCreatedTutorials[static_cast<EManagedTutorialTypes>(i)]->TriggerTutorialEnd(this);
					}

					continue; // Tutorial done, continue to next tutorial if anybhgyuo
				}
				else
				{
					if (mCreatedTutorials[static_cast<EManagedTutorialTypes>(i)]->IsActive() == false) // If tutorial not already triggered
					{
						// If time is up to trigger tutorial
						if (GetWorld()->GetRealTimeSeconds() - mInitTimestamp > mWaitTimeBeforeMovementTutorial)
						{
							mCreatedTutorials[static_cast<EManagedTutorialTypes>(i)]->TriggerTutorialStart(this);
							//mSpawnedBaseMovementTutorialWidget = TriggerBaseMovementTutorial(mBaseMovementTutorialWidgetClass); // Trigger the blueprint implemented tutorial func, so user can override however the tutorial gets added
						}
					}
				}
			}
		}
	}
}

