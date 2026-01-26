// Copyright (c) 2025 Guardbrawl Games

#pragma once

#include "Blueprint/UserWidget.h"
//#include "CoreMinimal.h"
//#include "UObject/NoExportTypes.h"
//#include "TutorialMonitor.h"
#include "StructDefinitionsFile.h"
#include "BaseTutorialConditions.generated.h"

UENUM(BlueprintType)
enum class ETutorialCompletionSaveType : uint8
{
	SaveOnlyForSession,
	SaveBetweenSessions,
	SaveForMonitorLifetime,
	DontSave
};


DECLARE_DYNAMIC_DELEGATE(FTutorialCompleteTriggerFunc);
DECLARE_DYNAMIC_DELEGATE(FTutorialTriggerFunc);

// Class for tutorial conditions as well as tutorial data /////////////////////////
UCLASS(Blueprintable)
class GGAMEUTILSTUTORIALSYSTEM_API UBaseTutorialConditions : public UObject
{
	GENERATED_BODY()

public:
	// Public interface /////////////////////////////////////////////////////////

	// Activates the tutorial. Sets variables, and calls UI setup
	void TriggerTutorialStart(APlayerController* controllerToAddTo);

	// Can be overwritten, or by default, creates tutorial widget, sets visual override data if that is enabled, and calls AddTutorialWidget
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InterfaceOverrides")
	void CallTutorialUISetup(APlayerController* controllerToAddTo);
	virtual void CallTutorialUISetup_Implementation(APlayerController* controllerToAddTo);

	// Can be overwritten to handle adding UI in a particular way. At it's base just adds the tutorial widget to the player's viewport
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InterfaceOverrides")
	void AddTutorialWidget(APlayerController* controllerToAddTo, UUserWidget* widgetPopup);
	virtual void AddTutorialWidget_Implementation(APlayerController* controllerToAddTo, UUserWidget* widgetPopup);

	// Deactivates the tutorial. Calls the overwritable OnTriggerTutorialEnd to determine how to close the tutorial
	void TriggerTutorialEnd(APlayerController* optionalPawnContext);

	// Closes tutorial UI. Can be overwritten to end tutorial using your own UI handling, and if overriding, make sure you remove the tutorial UI yourself, or add a call to the parent function
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InterfaceOverrides")
	void OnTriggerTutorialEnd(APlayerController* pawnContextToUse);
	virtual void OnTriggerTutorialEnd_Implementation(APlayerController* pawnContextToUse);


	// You can override to make your own completion condition, and it will end the tutorial when you return true
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Conditions")
	bool CheckTutorialComplete(APawn* pawnContextToUse); 
	virtual bool CheckTutorialComplete_Implementation(APawn* pawnContextToUse);

	// You can override to make your own activation condition, and it will activate the tutorial when you return true
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Conditions")
	bool CheckTutorialShouldActivate(APawn* pawnContextToUse);  
	virtual bool CheckTutorialShouldActivate_Implementation(APawn* pawnContextToUse);

	// Optional function to override to create any initialization logic you may want to happen right before the first activation check each restart.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Conditions")
	void InitializeOnFirstCheckToActivate(APawn* pawnContextToUse); 
	virtual void InitializeOnFirstCheckToActivate_Implementation(APawn* pawnContextToUse);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable,  Category = "BehaviourOverrides", meta=(ForceAsFunction))
	void ResetCustomVariables();
	virtual void ResetCustomVariables_Implementation();

	// Call alongside the CheckTutorialShouldActivate check, to call the initialization function
	UFUNCTION(BlueprintCallable, Category = "HelperFunctions")
	void InitializeIfNotAlready();

	// Gets pawn from parent tutorial monitor
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="GettersAndSetters")
	APawn* GetPawnFromParent();

	// Parent Overriden functions /////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category="TutorialContext")
	UWorld* GetWorld() const override;

	virtual bool ImplementsGetWorld() const;

	// Getters and setters ////////////////////////////////////////////////////////////////
	
	bool IsActive() const { return mIsActive; }

	bool IsCompleted() const { return mIsCurrentlyCompleted; }

	bool CancelIfConpletedBeforeTrigger() const { return mCancelIfCompletedBeforeTrigger; }

	float CurrentTriggerCheckWaitTime() const;

	bool WasManuallyTriggered() const { return mWasManuallyTriggered; }

	bool WasManuallyCompleted() const { return mWasManuallyCompleted; }

	// Gets real timestamp when tutorial was first able to start checking for activation. This is either when it was first constructed, or when it was last restarted
	UFUNCTION(BlueprintCallable, BlueprintPure, Category= "GettersAndSetters")
	float GetInitTimestamp() const { return mInitTimestamp; } 

	// Gets real timestamp when tutorial was triggered (not affected by time dillation)
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GettersAndSetters")
	float GetTriggeredTimestamp() const { return mTriggeredTimestamp; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GettersAndSetters")
	int GetMaxSavedCompletions() const { return mMaxSavedTutorialCompletions; }

	bool ShouldAutoEnd() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GettersAndSetters")
	bool ShouldResetOnceComplete() const { return mResetToReadyAfterCompleting; }

	ETutorialCompletionSaveType GetCompletionSaveType() const { return mSaveType; }

	FTutorialTriggerFunc GetTutorialTriggerDelegate();  // Gets a delegate that manually activates the tutorial when invoked

	FTutorialCompleteTriggerFunc GetTutorialCompleteTriggerDelegate(); // Gets a delegate that manually completes the tutorial when invoked



	void SetCompleted(bool newCompleted); // For manually setting a tutorial to be completed, like completing the condition before it pops up

	void SetManuallyTriggered(bool newTriggered);

	void SetManuallyCompleted(bool newManuallyCompleted);

	UFUNCTION(BlueprintCallable, Category="ManualTutorialManaging")
	void TrySetManuallyTriggered();

	UFUNCTION(BlueprintCallable, Category="ManualTutorialManaging")
	void TrySetManuallyCompleted();

	void SetInitTimestamp(float timestamp);

	/*
	For resetting the completion status
	Likely only needed for the automatic reset in the tutorial manager, which happens when the tutorial is completed, if the save type is set to don't save
	*/
	UFUNCTION(BlueprintCallable, Category="HelperFunctions")
	void ResetCompletionStatusToReady();

	// Blueprint editable variables ///////////////////////////////////////////////////////

	// Widget class to spawn for the tutorial. If using your own widget, implement the TutorialPopupInterface and its functions so it can be controlled by the tutorial
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	TSubclassOf<UUserWidget> mTutorialPopupClass; // Widget class to use for the tutorial popup


	// Other variables ///////////////////////////////////////////////////////
	UPROPERTY()
	UUserWidget* mCreatedTutorialWidget; // For saving the tutorial widget we spawn


protected:

	// If enabled, will check the completion condition before tutorial is triggered, allowing the tutorial not to be shown if completed before it's triggered
	UPROPERTY(EditDefaultsOnly, Category = "Completion Behaviour")
	bool mCancelIfCompletedBeforeTrigger = true;

	// How many tutorial completions that can happen before it won't be able trigger again (within the scope of its save type)
	UPROPERTY(EditAnywhere, Category = "Completion Behaviour")
	int mMaxSavedTutorialCompletions = 1; 

	// After tutorial completion, should the existing tutorial reset and allow itself to possibly be triggered again during this lifetime of the tutorial monitor
	UPROPERTY(EditAnywhere, Category="Completion Behaviour")
	bool mResetToReadyAfterCompleting = false; 


	UPROPERTY(EditDefaultsOnly, Category = "Triggering Behaviour")
	float mWaitTimeBeforeFirstTriggerCheck = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Triggering Behaviour")
	float mWaitTimeBeforeTriggerCheckAfterRestart = 0.0f;

	// Time after triggering when the tutorial will auto end. A 0 or negative value will make it not auto end, and only end when its condition is met, is manually completed, or cancelled by another tutorial
	UPROPERTY(EditDefaultsOnly, Category = "Completion Behaviour")
	float mAutoEndWaitTime = -1.0f; 

	// If true, overrides the below information on the tutorial widget through the ITutorialPopupInterface. Enables using the same widget for multiple tutorials
	UPROPERTY(EditAnywhere, Category = "Visuals")
	bool mUseVisualDataOverride = true;

	UPROPERTY(EditAnywhere, Category = "Visuals")
	FTutorialBasicVisualsData mVisualData;

	UPROPERTY(EditAnywhere, Category = "Saving Behaviour")
	ETutorialCompletionSaveType mSaveType = ETutorialCompletionSaveType::SaveOnlyForSession;


private:

	// Private variables
	// Make sure to reset any of these variables that should be reset when restarting a tutorial to be able to trigger it again, in the "ResetCompletionStatusToReady" function

	bool mIsActive = false;

	bool mIsCurrentlyCompleted = false;

	bool mWasManuallyTriggered = false;

	bool mWasManuallyCompleted = false;

	float mInitTimestamp = 0.0f;

	float mTriggeredTimestamp = 0.0f;

	bool mHasBeenRestarted = false;

	bool mWasInitialized = false;


};