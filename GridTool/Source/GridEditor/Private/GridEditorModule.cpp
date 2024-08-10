// Grid Tool Personal Project - AB - 04-2024

#include "GridEditorModule.h"
#include "ToolMenus.h"
#include "GridEditorToolkit.h"
#include "GridEditorToolkitSimple.h"

IMPLEMENT_MODULE(FGridEditorModule, GridEditor);

#define LOCTEXT_NAMESPACE "Grid"

void FGridEditorModule::StartupModule()
{
	RegisterMenu();
}

void FGridEditorModule::ShutdownModule()
{

}

void FGridEditorModule::RegisterMenu()
{
	// Create LevelEditor top menu
	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu");
		FToolMenuSection& Section = Menu->FindOrAddSection(NAME_None);

		FToolMenuEntry& GridEntry =
			Section.AddSubMenu(
				"Grid",
				LOCTEXT("GridMenu", "GridTools"),
				LOCTEXT("GridMenu_ToolTip", "Project Specific Grid Tools Menu"),
				FNewToolMenuChoice()
			);

		GridEntry.InsertPosition = FToolMenuInsert("Help", EToolMenuInsertType::After);
	}

	// Add specific entry to newly created grid menu
	{
		static const FName BaseMenuName = "LevelEditor.MainMenu.Grid"; // This add to the SubMenu added beforehand
		UToolMenu* Menu = UToolMenus::Get()->RegisterMenu(BaseMenuName, NAME_None, EMultiBoxType::Menu, /*bWarnIfAlreadyRegistered*/false);

		FToolMenuSection& Section = Menu->AddSection("General", LOCTEXT("GridEditorGeneral", "General"));
		Section.AddEntry(FToolMenuEntry::InitMenuEntry(
			"GridEditor",
			LOCTEXT("GridEditorName", "Grid Editor"),
			LOCTEXT("GridEditorToolTip", "Opens Grid Editor"),
			FSlateIcon(FAppStyle::GetAppStyleSetName(), "DeveloperTools.MenuIcon"), // TODO-AB change for better icon
			FUIAction(FExecuteAction::CreateRaw(this, &FGridEditorModule::OpenGridEditorCallback))
		));
	}
	
	// Add to Tools menu - more set as an example then anything else
	{
		UToolMenu* Menu = UToolMenus::Get()->FindMenu("LevelEditor.MainMenu.Tools");

		FToolMenuSection& Section = Menu->AddSection("GridEditor", LOCTEXT("GridEditor", "Grid Editor"));
		Section.AddEntry(FToolMenuEntry::InitMenuEntry(
			"GridEditor",
			LOCTEXT("GridEditorName", "Grid Editor"),
			LOCTEXT("GridEditorToolTip", "Opens Grid Editor"),
			FSlateIcon(FAppStyle::GetAppStyleSetName(), "DeveloperTools.MenuIcon"),
			FUIAction(FExecuteAction::CreateRaw(this, &FGridEditorModule::OpenGridEditorCallback))
		));
		Section.InsertPosition = FToolMenuInsert("WorldPartition", EToolMenuInsertType::After);
	}
}

void FGridEditorModule::OpenGridEditorCallback()
{
	MakeShared<FGridEditorToolkit>()->InitEditor();
	//MakeShared<FGridEditorToolkit>()->InitEditor();
}

#undef LOCTEXT_NAMESPACE