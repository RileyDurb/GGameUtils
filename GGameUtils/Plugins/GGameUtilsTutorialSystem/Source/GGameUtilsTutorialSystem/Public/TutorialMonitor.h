// Copyright (c) 2025 Guardbrawl Games

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
//#include "TimerManager.h"

#include "BaseTutorialConditions.h"
#include "DATutorialDefinitions.h"
#include "TutorialMonitor.generated.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Class responsible for updating tutorials, holding allocated ones, and managing their state
UCLASS( ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent) )
class GGAMEUTILSTUTORIALSYSTEM_API UTutorialMonitor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTutorialMonitor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	float mInitTimestamp = 0.0f; // Timestamp that the actor began play, for calculating some tutorial stuff

	// Public to make it a uproperty to manage the lifetime of UObjects, but for private logic use
	UPROPERTY(BlueprintReadWrite, Category="References")
	TMap<FGameplayTag, TObjectPtr<UBaseTutorialConditions>> mCreatedTutorials; // For holding created tutorials and using in tutorial logic


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Gets the player controller to use, based on what this component is attached to. By default supports attaching to a player controller, or the pawn it controls. Can override this
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, BlueprintPure, Category="TutorialContextOverride")
	APlayerController* GetPlayerControllerForTutorial();
	APlayerController* GetPlayerControllerForTutorial_Implementation();

	UFUNCTION(BlueprintCallable, Category= "TutorialTriggering")
	bool TryQueueTutorialTrigger(FGameplayTag tutorialToTrigger);

	// Gets a delagate that when called, will activate the tutorial. Meant for binding to an event dispacter
	UFUNCTION(BlueprintCallable, Category = "TutorialTriggering")
	FTutorialTriggerFunc GetTriggerTutorialDelegate(FGameplayTag tutorialToTrigger);

	// Gets a delagate that when called, will trigger the tutorial's completion. Meant for binding to an event dispacter
	UFUNCTION(BlueprintCallable, Category="TutorialEnding")
	FTutorialCompleteTriggerFunc GetTriggerTutorialCompleteDelegate(FGameplayTag tutorialToEnd);

	UFUNCTION(BlueprintCallable, Category = "TutorialEnding")
	bool TryQueueTutorialComplete(FGameplayTag tutorialToEnd);


	// Public editable variables for setting up tutorials

	// Data asset for which tutorials will be available in game.
	UPROPERTY(EditAnywhere, Category="DataAssets")
	UDATutorialDefinitions* mTutorialDefinitions;

private:
	// Helper functions
	bool CanTriggerTutorial(FGameplayTag tutorialTag);

	// Private variables

	FGameplayTagContainer mActiveTutorials;
};
