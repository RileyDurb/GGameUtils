// Copyright (c) 2025 Guardbrawl Games

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PrintPanelFunctions.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UPrintPanelFunctions : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GGAMEUTILS_API IPrintPanelFunctions
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void AddToPanelLog(const FString & message);
};
