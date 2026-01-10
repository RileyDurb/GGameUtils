// Copyright (c) 2025 Guardbrawl Games

#pragma once

#include "Blueprint/UserWidget.h"
//#include "CoreMinimal.h"
//#include "UObject/NoExportTypes.h"
//#include "TutorialMonitor.h"
#include "StructDefinitionsFile.h"
#include "BaseTutorialConditions.generated.h"



DECLARE_DYNAMIC_DELEGATE(FTutorialCompleteTriggerFunc);

// Class for tutorial conditions, to be transferred to it's own class file once we have a separate place to hold conditions /////////////////////////
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

	// Parent Overriden functions
	UFUNCTION(BlueprintCallable)
	UWorld* GetWorld() const override;

	// Getters and setters ////////////////////////////////////////////////////////////////
	
	bool IsActive() { return mIsActive; }

	bool IsCompleted() { return mIsCurrentlyCompleted; }

	bool CancelIfConpletedBeforeTrigger() { return mCancelIfCompletedBeforeTrigger; }

	float FirstTriggerCheckWaitTime() { return mWaitTimeBeforeFirstTriggerCheck; }

	bool WasManuallyTriggered() { return mWasManuallyTriggered; }

	bool WasManuallyCompleted() { return mWasManuallyCompleted; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category= "GettersNSetters")
	float GetInitTimestamp() { return mInitTimestamp; }

	FTutorialCompleteTriggerFunc GetTutorialCompleteTriggerDelegate(); // Gets a delegate that manually completes the tutorial when invoked

	void SetCompleted(bool newCompleted); // For manually setting a tutorial to be completed, like completing the condition before it pops up

	void SetManuallyTriggered(bool newTriggered);

	void SetManuallyCompleted(bool newManuallyCompleted);

	UFUNCTION()
	void TrySetManuallyCompleted();

	void SetInitTimestamp(float timestamp);

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

	// Behaviour Specifications
	UPROPERTY(EditDefaultsOnly)
	float mWaitTimeBeforeFirstTriggerCheck = 0.0f;

	UPROPERTY(EditAnywhere)
	bool mUseVisualDataOverride = true;

	UPROPERTY(EditAnywhere)
	FTutorialBasicVisualsData mVisualData;


private:
	//bool mHasTickCheck

	bool mIsActive = false;

	bool mIsCurrentlyCompleted = false;

	bool mWasManuallyTriggered = false;

	bool mWasManuallyCompleted = false;

	float mInitTimestamp = 0.0f;

};