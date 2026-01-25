// Copyright (c) 2025 Guardbrawl Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"

#include "GameplayTagContainer.h"
#include "TutorialMonitor.h"
#include "TutorialTriggerBoxBase.generated.h"

/**
 * 
 */
UCLASS()
class GGAMEUTILSTUTORIALSYSTEM_API ATutorialTriggerBoxBase : public ATriggerBox
{
	GENERATED_BODY()

public:
	void NotifyActorBeginOverlap(AActor* otherActor);

	// Decides whether to try triggering the tutorial when interacting with the actor. By default, interacts with locally controlled pawns that aren't bots
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Tutorial Monitor Location Overrides")
	bool ShouldTriggerFromActor(AActor* otherActor); 
	bool ShouldTriggerFromActor_Implementation(AActor* otherActor);

	// Gets the tutorial monitor from the given actor.
	// By default, makes sure it's a pawn, and then tries to get the component directly from the pawn, and if that doesn't work, tries to get it from the pawn's controller, to support attaching to the pawn or the player controller
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Tutorial Monitor Location Overrides")
	UTutorialMonitor* GetTutorialMonitorFromActor(AActor* otherActor);
	UTutorialMonitor* GetTutorialMonitorFromActor_Implementation(AActor* otherActor);
	
protected:
	UPROPERTY(EditAnywhere, Category="Setup Variables")
	FGameplayTag mTutorialTagToTrigger;
};
