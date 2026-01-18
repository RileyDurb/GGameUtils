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

	// Activates the tutorial. Can Be overwritten, or by default, calls add tutorial widget to create and add the popup to the owning pawn
	virtual void TriggerTutorialStart(APlayerController* monitoToAddTo);

	// Can be overwritten, but at it's base
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InterfaceOverrides")
	void AddTutorialWidget(APlayerController* controllerToAddTo, UUserWidget* widgetPopup);
	void AddTutorialWidget_Implementation(APlayerController* controllerToAddTo, UUserWidget* widgetPopup);

	// Deactivates the tutorial. Calls the overwritable OnTriggerTutorialEnd to determine what to do
	void TriggerTutorialEnd(APlayerController* optionalPawnContext);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InterfaceOverrides")
	void OnTriggerTutorialEnd(APlayerController* pawnContextToUse);
	virtual void OnTriggerTutorialEnd_Implementation(APlayerController* pawnContextToUse);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Conditions")
	bool CheckTutorialComplete(APawn* pawnContextToUse);
	virtual bool CheckTutorialComplete_Implementation(APawn* pawnContextToUse);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Conditions")
	bool CheckTutorialShouldActivate(APawn* pawnContextToUse);
	virtual bool CheckTutorialShouldActivate_Implementation(APawn* pawnContextToUse);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable,  Category = "BehaviourOverrides", meta=(ForceAsFunction))
	void ResetCustomVariables();
	virtual void ResetCustomVariables_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="GettersAndSetters")
	APawn* GetPawnFromParent(); // Gets pawn from parent tutorial monitor
	// Parent Overriden functions /////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable)
	UWorld* GetWorld() const override;

	bool ImplementsGetWorld() const override;

	// Getters and setters ////////////////////////////////////////////////////////////////
	
	bool IsActive() const { return mIsActive; }

	bool IsCompleted() const { return mIsCurrentlyCompleted; }

	bool CancelIfConpletedBeforeTrigger() const { return mCancelIfCompletedBeforeTrigger; }

	float CurrentTriggerCheckWaitTime() const;

	bool WasManuallyTriggered() const { return mWasManuallyTriggered; }

	bool WasManuallyCompleted() const { return mWasManuallyCompleted; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category= "GettersAndSetters")
	float GetInitTimestamp() const { return mInitTimestamp; } // Gets real timestamp when tutorial was first set active, either when it was first constructed, or after being completed, if it is set to restart.

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GettersAndSetters")
	float GetTriggeredTimestamp() const { return mTriggeredTimestamp; } // Gets real timestamp when tutorial was triggered

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GettersAndSetters")
	int GetMaxSavedCompletions() const { return mMaxSavedTutorialCompletions; }

	bool ShouldAutoEnd() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GettersAndSetters")
	bool ShouldResetOnceComplete() const { return mResetToReadyAfterCompleting; }

	ETutorialCompletionSaveType GetCompletionSaveType() const { return mSaveType; }

	FTutorialTriggerFunc GetTutorialTriggerDelegate();

	FTutorialCompleteTriggerFunc GetTutorialCompleteTriggerDelegate(); // Gets a delegate that manually completes the tutorial when invoked



	void SetCompleted(bool newCompleted); // For manually setting a tutorial to be completed, like completing the condition before it pops up

	void SetManuallyTriggered(bool newTriggered);

	void SetManuallyCompleted(bool newManuallyCompleted);

	UFUNCTION(BlueprintCallable)
	void TrySetManuallyTriggered();

	UFUNCTION(BlueprintCallable)
	void TrySetManuallyCompleted();

	void SetInitTimestamp(float timestamp);

	/*
	For resetting the completion status
	Likely only needed for the automatic reset in the tutorial manager, which happens when the tutorial is completed, if the save type is set to don't save
	*/
	UFUNCTION(BlueprintCallable)
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
	//bool mHasTickCheck

	// Private variables

	bool mIsActive = false;

	bool mIsCurrentlyCompleted = false;

	bool mWasManuallyTriggered = false;

	bool mWasManuallyCompleted = false;

	float mInitTimestamp = 0.0f;

	float mTriggeredTimestamp = 0.0f;

	bool mHasBeenRestarted = false;


};