// Copyright (c) 2026 Guardbrawl Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "BaseTutorialConditions.h"
#include "DATutorialDefinitions.generated.h"


// Class for data asset to hold tutorials, to be transferred to it's own class file once we have a separate place to hold conditions /////////////////////////
UCLASS(Blueprintable)
class GGAMEUTILSTUTORIALSYSTEM_API UDATutorialDefinitions : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "TutorialDefinitions")
	TMap<FGameplayTag, TSubclassOf<UBaseTutorialConditions>> mTutorials;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AddtionalSettings")
	TMap<FGameplayTag, FGameplayTagContainer> mTutorialsCanCancelWhichTutorials;

};