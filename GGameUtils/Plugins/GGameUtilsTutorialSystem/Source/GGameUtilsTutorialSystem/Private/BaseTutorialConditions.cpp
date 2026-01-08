// Copyright (c) 2025 Guardbrawl Games


#include "BaseTutorialConditions.h"
#include "GameFramework/Pawn.h"
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


void UBaseTutorialConditions::TriggerTutorialStart(APlayerController* controllerToUse)
{

	mCreatedTutorialWidget = CreateWidget(controllerToUse, mTutorialPopupClass);

	AddTutorialWidget(controllerToUse, mCreatedTutorialWidget); // Handles adding to viewport, letting how the widget is added be overwritten if UI is handled in a particular way

	mIsActive = true;
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