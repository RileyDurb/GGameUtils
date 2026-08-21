// Copyright (c) 2025 Guardbrawl Games

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Blueprint/UserWidget.h"
#include "DebugPrintPanel.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GGAMEUTILS_API UDebugPrintPanel : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDebugPrintPanel();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable, Category="DebugPrinting")
	void AddToLog(FString message);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	TSubclassOf<UUserWidget> mPrintPanelPopupClass; // Widget class to display debug prints on

	UPROPERTY(BlueprintReadWrite)
	UUserWidget* mSpawnedPanelWidget;

private:
	void SetPanelActiveState(bool newIsActive);


	bool mPanelActive = false;
};
