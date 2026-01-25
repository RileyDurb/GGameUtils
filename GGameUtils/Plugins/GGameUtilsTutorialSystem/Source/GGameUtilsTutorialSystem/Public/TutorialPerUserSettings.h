// Copyright (c) 2025 Guardbrawl Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "TutorialPerUserSettings.generated.h"

/**
 * 
 */
UCLASS(config = EditorPerProjectUserSettings, meta = (DisplayName = "GGameUtils TutorialSystem", ClassGroup = Plugins))
class GGAMEUTILSTUTORIALSYSTEM_API UTutorialPerUserSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, config, Category="Saving", meta = (Tooltip = "Whether to ignore saving tutorial states between sessions in editor. On by default, so you can test tutorials each time you play in editor"))
	bool IgnorePersistentTutorialSavesInEditor = true;

	static const UTutorialPerUserSettings* Get() { return GetDefault<UTutorialPerUserSettings>(); }
};
