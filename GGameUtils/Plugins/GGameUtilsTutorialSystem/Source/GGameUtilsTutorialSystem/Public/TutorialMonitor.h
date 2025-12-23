// Copyright (c) 2025 Guardbrawl Games

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Blueprint/UserWidget.h"
//#include ""
#include "TutorialMonitor.generated.h"

UENUM()
enum class EManagedTutorialTypes : uint8
{
	BaseMoveAndAim,
	Max
};

// Class for data asset to hold tutorials, to be transferred to it's own class file once we have a separate place to hold conditions /////////////////////////
UCLASS(Blueprintable)
class GGAMEUTILSTUTORIALSYSTEM_API UDATutorialDefinitions : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EManagedTutorialTypes, TSubclassOf<UBaseTutorialConditions>> mTutorials;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Class for tutorial conditions, to be transferred to it's own class file once we have a separate place to hold conditions /////////////////////////
UCLASS(Blueprintable)
class GGAMEUTILSTUTORIALSYSTEM_API UBaseTutorialConditions : public UObject
{
	GENERATED_BODY()

public:
	// Public interface /////////////////////////////////////////////////////////
	
	// Activates the tutorial. Can Be overwritten, or by default, calls add tutorial widget to create and add the popup to the owning pawn
	virtual void TriggerTutorialStart(UTutorialMonitor* monitoToAddTo);

	// Can be overwritten, but at it's base
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InterfaceOverrides")
	void AddTutorialWidget(UTutorialMonitor* monitoToAddTo, UUserWidget* widgetPopup);
	void AddTutorialWidget_Implementation(UTutorialMonitor* monitoToAddTo, UUserWidget* widgetPopup);

	// Deactivates the tutorial. Can be overwritten, or by default, calls the end interface of the widget created
	virtual void TriggerTutorialEnd(UTutorialMonitor* monitoToAddTo);



	bool IsActive() { return mIsActive; }

	// Blueprint editable variables ///////////////////////////////////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> mTutorialPopupClass; // Widget class to use for the tutorial popup


	// Other variables ///////////////////////////////////////////////////////
	UPROPERTY()
	UUserWidget* mCreatedTutorialWidget; // For saving the tutorial widget we spawn


private:
	//bool mHasTickCheck

	bool mIsActive = false;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	TMap<EManagedTutorialTypes, bool> mTutorialStates;

	float mInitTimestamp = 0.0f; // Timestamp that the actor began play, for calculating some tutorial stuff

	// Turn these into peices of a base tutorial definition object

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "TempSpecificTutorialChecks")
	bool CheckBaseMoveTutorialComplete();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TempSpecificTutorialChecks")
	float mWaitTimeBeforeMovementTutorial = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TempSpecificTutorialChecks")
	TSubclassOf<UUserWidget> mBaseMovementTutorialWidgetClass;

	UPROPERTY()
	UUserWidget* mSpawnedBaseMovementTutorialWidget = nullptr; // Saved reference to the spawned base movement tutorial widget


	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	UUserWidget* TriggerBaseMovementTutorial(TSubclassOf<UUserWidget> widgetToSpawn);

	UPROPERTY(EditAnywhere)
	UDATutorialDefinitions* mTutorialDefinitions;

	UPROPERTY(BlueprintReadWrite)
	TMap<EManagedTutorialTypes, TObjectPtr<UBaseTutorialConditions>> mCreatedTutorials;

};
