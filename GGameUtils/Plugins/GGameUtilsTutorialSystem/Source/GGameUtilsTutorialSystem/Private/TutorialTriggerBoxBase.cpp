// Copyright (c) 2025 Guardbrawl Games



#include "TutorialTriggerBoxBase.h"


void ATutorialTriggerBoxBase::NotifyActorBeginOverlap(AActor* otherActor)
{
	Super::NotifyActorBeginOverlap(otherActor);

	// Makes sure it should trigger from this actor, by default making sure it's a player pawn
	if (ShouldTriggerFromActor(otherActor) == false)
	{
		return;
	}

	UTutorialMonitor* tutorialMonitor = GetTutorialMonitorFromActor(otherActor);

	if (tutorialMonitor == nullptr)
	{
		return;
	}

	tutorialMonitor->TryQueueTutorialTrigger(mTutorialTagToTrigger);
}

bool ATutorialTriggerBoxBase::ShouldTriggerFromActor_Implementation(AActor* otherActor)
{
	// Only try triggering a tutorial if interacting with a pawn
	if (otherActor->IsA<APawn>() == false)
	{
		return false;
	}

	APawn* interactedPawn = Cast<APawn>(otherActor);

	// If locally controlled, so the local player on the client, and not bot controlled (to avoid bots triggering the tutorials), allow tutorial trigger
	return interactedPawn->IsLocallyControlled() && interactedPawn->IsBotControlled() == false;
}

UTutorialMonitor* ATutorialTriggerBoxBase::GetTutorialMonitorFromActor_Implementation(AActor* otherActor)
{
	// By default, only accept a pawn
	if (otherActor->IsA<APawn>() == false)
	{
		return nullptr;
	}

	// First tries to get the tutorial monitor from the pawn itself
	UTutorialMonitor* tutorialMonitor = otherActor->GetComponentByClass<UTutorialMonitor>();

	if (tutorialMonitor != nullptr)
	{
		return tutorialMonitor; // Tutorial manager was on the pawn, succeeded, and return it
	}

	// If there was no monitor on the pawn, tries to get it from the pawn's controller, which we also support
	APlayerController* playerController = Cast<APlayerController>(Cast<APawn>(otherActor)->GetController());

	if (playerController == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("TutorialTriggerBoxBase:GetTutorialMonitorFromActor_Implementation: No tutorial manager was found on the given pawn, and pawn has no controller to look for a tutorial manager on. Should add one, or override this function to get it from somewhere else"));
		return nullptr; // No player controller to get the component from, return failiure
	}

	tutorialMonitor = playerController->GetComponentByClass<UTutorialMonitor>();

	if (tutorialMonitor == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("TutorialTriggerBoxBase:GetTutorialMonitorFromActor_Implementation: No tutorial manager was found on the given pawn or it's controller. Add one, or override this function to get it from somewhere else"));
		return nullptr;
	}

	return tutorialMonitor; // Valid tutorial monitor was found on the pawn's player controller. Success, and return it
}

