// Copyright (c) 2026 Guardbrawl Games

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FTutorialSysEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual bool IsGameModule() const override
	{
		return true;
	}
};
