// Copyright (c) 2025 Guardbrawl Games

#pragma once

#include "CoreMinimal.h"
#include "BaseTutorialConditions.h"

#include "NativeGameplayTags.h"
#include "GameFramework/Pawn.h"
#include "TutorialConditions_ShootControls.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(GGameUtils_Tutorials_CPPShootTutorial);
/**
 * 
 */
UCLASS()
class GGAMEUTILS_API UTutorialConditions_ShootControls : public UBaseTutorialConditions
{
	GENERATED_BODY()
public:

	UTutorialConditions_ShootControls();

};
