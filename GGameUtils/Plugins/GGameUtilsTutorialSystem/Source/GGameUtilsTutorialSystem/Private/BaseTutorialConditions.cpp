// Copyright (c) 2025 Guardbrawl Games


#include "BaseTutorialConditions.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "TutorialMonitor.h"
#include "TutorialPopupInterface.h"


//void UBaseTutorialConditions::TriggerTutorial(UTutorialMonitor* monitorToAddTo)
//{
//	APawn* ownerPawn = Cast<APawn>(monitorToAddTo->GetOwner());
//
//	// Make sure owner is a pawn, put a debug message and return if not
//	if (ownerPawn == nullptr)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("UBaseTutorialConditions:AddTutorialWidget:monitor with owner of class %s was not a pawn. Reccomend overriding this function to support your own setup.", *monitorToAddTo->GetOwner()->GetActorNameOrLabel()));
//
//		return;
//	}
//
//	mCreatedTutorialWidget = CreateWidget(ownerPawn->GetLocalViewingPlayerController(), mTutorialPopupClass);
//		
//	AddTutorialWidget(monitorToAddTo, mCreatedTutorialWidget); // Handles adding to viewport, letting how the widget is added be overwritten if UI is handled in a particular way
//}
//
//void UBaseTutorialConditions::AddTutorialWidget(UTutorialMonitor* monitorToAddTo, UUserWidget* widgetPopup)
//{
//	APawn* ownerPawn = Cast<APawn>(monitorToAddTo->GetOwner());
//
//	// Make sure owner is a pawn, put a debug message and return if not
//	if (ownerPawn == nullptr)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("UBaseTutorialConditions:AddTutorialWidget:monitor with owner of class %s was not a pawn. Reccomend overriding this function to support your own setup.", *monitorToAddTo->GetOwner()->GetActorNameOrLabel()));
//
//		return;
//	}
//
//	widgetPopup->AddToViewport();
//}

// Private helper functions ////////////////////////////////////////////////////////////////////////////////////////

APawn* GetTutorialPlayerFromOuter(UBaseTutorialConditions* tutorialToUse)
{
	return Cast<UTutorialMonitor>(tutorialToUse->GetOuter())->GetPlayerControllerForTutorial()->GetPawn();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Class functions /////////////////////////////////////////////////////////////////////////////////////////////////

void UBaseTutorialConditions::TriggerTutorialStart(APlayerController* controllerToUse)
{

	mCreatedTutorialWidget = CreateWidget(controllerToUse, mTutorialPopupClass);

	if (mUseVisualDataOverride)
	{
		if (mCreatedTutorialWidget->GetClass()->ImplementsInterface(UTutorialPopupInterface::StaticClass()))
		{

			ITutorialPopupInterface::Execute_ApplyVisualDataOverride(mCreatedTutorialWidget, mVisualData);
		}
	}


	AddTutorialWidget(controllerToUse, mCreatedTutorialWidget); // Handles adding to viewport, letting how the widget is added be overwritten if UI is handled in a particular way

	mIsActive = true;

	mTriggeredTimestamp = GetWorld()->GetRealTimeSeconds();
}

void UBaseTutorialConditions::AddTutorialWidget_Implementation(APlayerController* controlerUsed, UUserWidget* widgetPopup)
{
	// NOTE: Doesn't need the controller used in the base function, but takes a reference so that it has the context of the controller used to get whatever may be needed for a derived implementation

	// Adds already created widget to the viewport
	widgetPopup->AddToViewport();
}
bool UBaseTutorialConditions::CheckTutorialComplete_Implementation(APawn* pawnContextToUse)
{
	return true;
}

bool UBaseTutorialConditions::CheckTutorialShouldActivate_Implementation(APawn* pawnContextToUse)
{
	return false;
}

void UBaseTutorialConditions::ResetCustomVariables_Implementation()
{
	// Does nothing by default, base variables already reset as a part of the code that calls this function
}

APawn* UBaseTutorialConditions::GetPawnFromParent()
{
	return GetTutorialPlayerFromOuter(this);
}

UWorld* UBaseTutorialConditions::GetWorld() const
{
	return GetOuter()->GetWorld(); // Returns parent's world
}

bool UBaseTutorialConditions::ImplementsGetWorld() const
{
	return true;
}

bool UBaseTutorialConditions::ShouldAutoEnd() const
{
	// Only auto end with positive wait time values. negative or 0 counts as never auto ending
	if (mAutoEndWaitTime <= 0.0f)
	{
		return false;
	}

	// If auto wait time is up
	if (GetWorld()->GetRealTimeSeconds() - mTriggeredTimestamp > mAutoEndWaitTime)
	{
		return true;
	}
	else
	{
		return false;
	}
}

FTutorialTriggerFunc UBaseTutorialConditions::GetTutorialTriggerDelegate()
{
	FTutorialTriggerFunc triggerFunc;
	triggerFunc.BindUFunction(this, "TrySetManuallyTriggered");

	return triggerFunc;
}

FTutorialCompleteTriggerFunc UBaseTutorialConditions::GetTutorialCompleteTriggerDelegate()
{
	FTutorialCompleteTriggerFunc triggerFunc;
	triggerFunc.BindUFunction(this, "TrySetManuallyCompleted");

	return triggerFunc;
}

void UBaseTutorialConditions::SetCompleted(bool newCompleted)
{
	mIsCurrentlyCompleted = newCompleted;
}

void UBaseTutorialConditions::SetManuallyTriggered(bool newTriggered)
{
	mWasManuallyTriggered = newTriggered;
}

void UBaseTutorialConditions::SetManuallyCompleted(bool newManuallyCompleted)
{
	mWasManuallyCompleted = newManuallyCompleted;
}

void UBaseTutorialConditions::TrySetManuallyTriggered()
{
	// If case not needed here if no more logic is added, but may want to add logic to potentailly stop it from bein manually triggered if we don't want it now
	if (mWasManuallyTriggered == false)
	{
		mWasManuallyTriggered = true;
	}
}

// Bindable Version that doesn't take a parameter
void UBaseTutorialConditions::TrySetManuallyCompleted()
{
	// If case not needed here if no more logic is added, but may want to add logic to potentailly stop it from bein manually completed if we don't want it now
	if (mWasManuallyCompleted == false)
	{
		mWasManuallyCompleted = true;
	}
}

void UBaseTutorialConditions::SetInitTimestamp(float timestamp)
{
	mInitTimestamp = timestamp;
}

void UBaseTutorialConditions::ResetCompletionStatusToReady()
{
	// Reset all state variables, so that it can be triggered again just like when it was first initialized
	mIsActive = false;
	mIsCurrentlyCompleted = false;
	mWasManuallyTriggered = false;
	mWasManuallyCompleted = false;

	mInitTimestamp = GetWorld()->GetRealTimeSeconds(); // Reset init timestamp to now

	ResetCustomVariables(); // Calls overridable reset variables function, to let the derived tutorial reset any variables it may have created that need it
}

void UBaseTutorialConditions::TriggerTutorialEnd(APlayerController* controllerContext)
{

	OnTriggerTutorialEnd(controllerContext);

	/* Immediately sets is active to false, but may need to delay the setting of false till the the animation of the tutorial end completes
	- One idea is to pass a listener for the widget to call when done
	- another is to make another interface function that gets the time till the end
	*/
	mIsActive = false;
	mIsCurrentlyCompleted = true;
}


void UBaseTutorialConditions::OnTriggerTutorialEnd_Implementation(APlayerController* controllerContext)
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
}

