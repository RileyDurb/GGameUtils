// Copyright (c) 2025 Guardbrawl Games


//#include "BaseTutorialConditions.h"
//#include "GameFramework/Pawn.h"
//
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
