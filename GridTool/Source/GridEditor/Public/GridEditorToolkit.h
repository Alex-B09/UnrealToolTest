// Grid Tool Personal Project - AB - 04-2024

#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"


/**
 * This is a test to see if I can create my own toolkit
 * I still have questions about modes and LocalWorkspaceMenuCategory but we'll answer them in time
 * 
 * From my understanding, the goal of the toolkit is to
 *		Set Name, Icons and other data
 *		Map actions
 *		Create/Populate Toolbar
 *		Create/Populate Menus
 *		Create/Manage Modes (?)
 *		Handle Open/Close
 *		Create window
 */
class FGridEditorToolkit : 
	public FBaseToolkit, 
	public TSharedFromThis<FGridEditorToolkit>
{
public:
	void InitEditor();

	virtual FName GetToolkitFName() const override { return "GridEditor"; }
	virtual FText GetBaseToolkitName() const override { return INVTEXT("Grid Editor Window"); }
	virtual FString GetWorldCentricTabPrefix() const override { return "Grid Editor"; }
	//virtual void InvokeTab(const struct FTabId& TabId) override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return {}; }

	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;

	virtual FText GetToolkitName() const override { return INVTEXT("Look Mom, I'm an UE tool"); };

	virtual FEditorModeTools& GetEditorModeManager() const override;
	virtual FText GetToolkitToolTipText() const override;
	virtual bool IsAssetEditor() const override;
	virtual const TArray<UObject*>* GetObjectsCurrentlyBeingEdited() const override;

	void AddMenuExtender(TSharedPtr<FExtender> Extender);
	TSharedPtr<FExtensibilityManager> GetSharedMenuExtensibilityManager();
	TSharedPtr<FExtensibilityManager> GetSharedToolbarExtensibilityManager();

	TSharedPtr<class SGridEditorToolkitHost> GetGetEditorToolkitHost();

private:
	void OnPersistLayout(const TSharedRef<FTabManager::FLayout>& Layout);


protected:
	/** The editor mode manager */
	TSharedPtr<FEditorModeTools> EditorModeManager;

	/** Tab manager for this toolkit - We try to be as self-contained as possible*/
	TSharedPtr<FTabManager> ToolkitTabManager;

private:
	TSharedPtr<FExtensibilityManager> SharedMenuExtensibilityManager; // All extenders for the Menu
	TSharedPtr<FExtensibilityManager> SharedToolbarExtensibilityManager; // All extenders for the Toolbar
};
