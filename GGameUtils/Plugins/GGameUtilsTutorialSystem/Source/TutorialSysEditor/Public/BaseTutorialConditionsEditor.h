// Copyright (c) 2025 Guardbrawl Games

#pragma once

#include "CoreMinimal.h"
//#if WITH_EDITOR
#include "Editor/DetailCustomizations/Public/DetailCustomizations.h"
#include "Editor/PropertyEditor/Public/IDetailCustomization.h"



/**
 * Class for adding a button that opens up the widget preview editor utility widget to the class defaults of the tutorial blueprints
 */
class FBaseTutorialConditionsEditor : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void CustomizeDetails(IDetailLayoutBuilder& detailBuilder) override;

};



//#endif
