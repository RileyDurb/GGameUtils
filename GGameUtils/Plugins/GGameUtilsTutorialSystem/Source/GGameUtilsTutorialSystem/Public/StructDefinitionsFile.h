// Copyright (c) 2025 Guardbrawl Games

#pragma once

#include "CoreMinimal.h"
#include "StructDefinitionsFile.generated.h"

USTRUCT(BlueprintType)
struct GGAMEUTILSTUTORIALSYSTEM_API FTutorialBasicVisualsData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Text", meta=(Multiline = true))
	FText tutorialTextOverride;

	// Data table made from type "RichTextStyleRow" That you can use to define the text's font, size and more. Reccomend not doing anything it user leaves this variable left blank
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
	UDataTable* textStyleDataTable;

};

/**
 * 
 */
class GGAMEUTILSTUTORIALSYSTEM_API StructDefinitionsFile
{
public:
	StructDefinitionsFile();
	~StructDefinitionsFile();
};
