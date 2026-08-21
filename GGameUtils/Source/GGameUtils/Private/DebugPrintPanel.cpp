// Copyright (c) 2025 Guardbrawl Games


#include "DebugPrintPanel.h"
#include "PrintPanelFunctions.h"
// Sets default values for this component's properties
UDebugPrintPanel::UDebugPrintPanel()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDebugPrintPanel::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDebugPrintPanel::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (mPanelActive == false)
	{
		SetPanelActiveState(true);
	}
	// ...
}

void UDebugPrintPanel::AddToLog(FString message)
{
	// Activate panel if not already there
	if (mSpawnedPanelWidget == NULL && mPanelActive == false)
	{
		SetPanelActiveState(true);
	}

	if (mSpawnedPanelWidget->GetClass()->ImplementsInterface(UPrintPanelFunctions::StaticClass()))
	{
		IPrintPanelFunctions::Execute_AddToPanelLog(mSpawnedPanelWidget, message);
	}
}

void UDebugPrintPanel::SetPanelActiveState(bool newIsActive)
{
	if (newIsActive == mPanelActive)
	{
		return; // Don't change panel active state if already in the desired state
	}

	if (newIsActive == true)
	{
		// If no panel widget has been created
		if (mSpawnedPanelWidget == NULL)
		{
			APawn* owningPawn = Cast<APawn>(GetOwner());
			if (owningPawn == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("UDebugPrintPanel:SetPanelActiveState: Owner is not a pawn, cannot create widget"));
				return;
			}

			APlayerController* owningController = Cast<APlayerController>(owningPawn->GetController());
			if (owningController == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("UDebugPrintPanel:SetPanelActiveState: Owner's controller is not a player controller, cannot create widget"));
				return;
			}

			// Create the panel widget
			UUserWidget* panelWidget = CreateWidget(owningController, mPrintPanelPopupClass);

			panelWidget->AddToViewport();

			mSpawnedPanelWidget = panelWidget;
		}
		else // Just make the existing widget visible again
		{
			mSpawnedPanelWidget->SetVisibility(ESlateVisibility::Visible);
		}

		mPanelActive = true;
	}
	else
	{
		mSpawnedPanelWidget->SetVisibility(ESlateVisibility::Collapsed);
		mPanelActive = false;
	}
}

