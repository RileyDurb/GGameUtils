// Copyright (c) 2025 Guardbrawl Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BaseTutorialConditions.h"
#include "GameplayTagContainer.h"
#include "InstancedTutorialData.generated.h"

USTRUCT(BlueprintType)
struct GGAMEUTILSTUTORIALSYSTEM_API FInstancedTutorialRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identifier")
	FGameplayTag tutorialTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TutorialDefinition")
	TArray<TSubclassOf<UBaseTutorialConditions>> tutorialDefinitionClass;

};

/**
 *
 */

/**
 * 
 */
//class GGAMEUTILSTUTORIALSYSTEM_API InstancedTutorialData
//{
//public:
//	InstancedTutorialData();
//	~InstancedTutorialData();
//};
