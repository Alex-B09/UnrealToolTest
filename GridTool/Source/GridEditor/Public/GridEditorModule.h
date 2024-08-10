// Grid Tool Personal Project - AB - 04-2024

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FGridEditorModule : public IModuleInterface
{
public:
	void StartupModule() override;
	void ShutdownModule() override;

private:
	void RegisterMenu();

	void OpenGridEditorCallback();
};