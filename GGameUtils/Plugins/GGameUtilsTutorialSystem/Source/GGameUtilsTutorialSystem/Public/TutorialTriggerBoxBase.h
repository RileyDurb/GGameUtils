// Copyright (c) 2025 Guardbrawl Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"

#include "GameplayTagContainer.h"
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
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool ShouldTriggerFromActor(AActor* otherActor); 
	bool ShouldTriggerFromActor_Implementation(AActor* otherActor);
	
protected:
	UPROPERTY(EditAnywhere)
	FGameplayTag mTutorialTagToTrigger;
};
