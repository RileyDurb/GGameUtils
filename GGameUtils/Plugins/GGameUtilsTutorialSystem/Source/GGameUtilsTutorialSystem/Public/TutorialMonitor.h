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

};
