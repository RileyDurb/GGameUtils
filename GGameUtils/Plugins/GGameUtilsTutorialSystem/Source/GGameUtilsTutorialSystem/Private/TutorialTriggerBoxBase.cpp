// Copyright (c) 2025 Guardbrawl Games

#include "TutorialMonitor.h"

#include "TutorialTriggerBoxBase.h"

void ATutorialTriggerBoxBase::NotifyActorBeginOverlap(AActor* otherActor)
{
	Super::NotifyActorBeginOverlap(otherActor);

	// Makes sure it should trigger from this actor, by default making sure it's a player pawn
	if (ShouldTriggerFromActor(otherActor) == false)
	{
		return;
	}

	UTutorialMonitor* tutorialMonitor = otherActor->GetComponentByClass<UTutorialMonitor>();

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

