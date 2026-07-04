// Copyright (c) 2025 Guardbrawl Games

#pragma once

#include "CoreMinimal.h"

#include "NativeGameplayTags.h"
#include "DefaultTutorialTagDefs.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(GGameUtils_Tutorials_ExampleHey1);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(GGameUtils_Tutorials_ExampleHey2);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(GGameUtils_Tutorials_ExampleHey3);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(GGameUtils_Tutorials_ExampleHey4);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(GGameUtils_Tutorials_ExampleHey5);

/**
 * 
 */
UCLASS()
class GGAMEUTILSTUTORIALSYSTEM_API UDefaultTutorialTagDefs : public UObject
{
	GENERATED_BODY()
public:
	UDefaultTutorialTagDefs();
	~UDefaultTutorialTagDefs();
};
