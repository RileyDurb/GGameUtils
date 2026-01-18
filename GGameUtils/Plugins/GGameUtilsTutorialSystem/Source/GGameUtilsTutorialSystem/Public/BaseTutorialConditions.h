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
	DontSaveAndResetToReady
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

	UFUNCTION(BlueprintCallable, BlueprintPure, Category= "GettersNSetters")
	float GetInitTimestamp() const { return mInitTimestamp; } // Gets real timestamp when tutorial was first set active, either when it was first constructed, or after being completed, if it is set to restart.

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GettersNSetters")
	float GetTriggeredTimestamp() const { return mTriggeredTimestamp; } // Gets real timestamp when tutorial was triggered

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GettersAndSetters")
	int GetMaxSavedCompletions() const { return mMaxSavedTutorialCompletions; }

	bool ShouldAutoEnd() const;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> mTutorialPopupClass; // Widget class to use for the tutorial popup


	// Other variables ///////////////////////////////////////////////////////
	UPROPERTY()
	UUserWidget* mCreatedTutorialWidget; // For saving the tutorial widget we spawn


protected:
	// Behaviour Specifications

	UPROPERTY(EditDefaultsOnly)
	bool mCancelIfCompletedBeforeTrigger = true;

	UPROPERTY(EditAnywhere)
	int mMaxSavedTutorialCompletions = 1; // While it will only trigger again right away if save type is set to restart, this lets you set a higher number of tutorial completions that can happen before it won't trigger again.

	// Behaviour Specifications
	UPROPERTY(EditDefaultsOnly)
	float mWaitTimeBeforeFirstTriggerCheck = 0.0f;

	UPROPERTY(EditDefaultsOnly)
	float mWaitTimeBeforeTriggerCheckAfterRestart = 0.0f;

	UPROPERTY(EditDefaultsOnly)
	float mAutoEndWaitTime = -1.0f; // Time after triggering, when the tutorial will auto end. A 0 or negative value will make it not auto end

	UPROPERTY(EditAnywhere)
	bool mUseVisualDataOverride = true;

	UPROPERTY(EditAnywhere)
	FTutorialBasicVisualsData mVisualData;

	UPROPERTY(EditAnywhere)
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