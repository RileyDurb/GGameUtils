// Copyright (c) 2025 Guardbrawl Games

#pragma once

#include "CoreMinimal.h"
#include "StructDefinitionsFile.generated.h"

USTRUCT(BlueprintType)
struct GGAMEUTILSTUTORIALSYSTEM_API FTutorialBasicVisualsData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Text")
	FText tutorialTextOverride;

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
