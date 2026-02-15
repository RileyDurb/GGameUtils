// Copyright (c) 2026 Guardbrawl Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "StructDefinitionsFile.generated.h"

USTRUCT(BlueprintType)
struct GGAMEUTILSTUTORIALSYSTEM_API FTutorialBasicVisualsData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Text", meta=(Multiline = true))
	FText tutorialTextOverride;

	// Data table made from type "RichTextStyleRow" that you can use to define the text's font, size and more. Reccomend not doing anything it user leaves this variable left blank
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
	UDataTable* textStyleDataTable = nullptr;

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
