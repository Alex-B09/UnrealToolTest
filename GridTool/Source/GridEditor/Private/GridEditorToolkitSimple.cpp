// Grid Tool Personal Project - AB - 04-2024


#include "GridEditorToolkitSimple.h"
#include "GridEditorToolkitHost.h"
#include "GridEditorWidget.h"


#include "EditorModeManager.h"
#include "Misc/Attribute.h"
#include "Toolkits/GlobalEditorCommonCommands.h"
#include "Toolkits/ToolkitManager.h"
#include "UnrealEdMisc.h"
#include "Templates/SharedPointer.h"

UE_DISABLE_OPTIMIZATION

namespace
{
	TSharedPtr<FExtensibilityManager> SharedExtensibilityManager;
	FName DefaultParentToolbarName("GridEditor.DefaultToolbar");
	FName DefaultToolbarName("GridEditor.Current.DefaultToolbar");
};

void FGridEditorToolkitSimple::InitEditor()
{
	FToolkitManager& ToolkitManager = FToolkitManager::Get();
	//------------------------------------------------
	// STEP 0 - Validate prerequisite
	//			Am I already open?
	//			do I have asset? -- should not matter much to me though
	//			Seems a bit impossible with the current ToolkitManager setup
	//			it only works for asset editors
	//			so cache a static entity of this?


	//------------------------------------------------
	// STEP 1 - Register itself to be worthy of life
	//			If not, we may loose the reference to this toolkit
	//			An other solution would be to be a singleton
	
	// INFO 	Toolkit Manager stores the existing toolkits
	//			Can be useful to find already opened toolkit and bringing them on top
	
	//check(ToolkitManager.IsValid());
	//ToolkitManager.RegisterNewToolkit(SharedThis(this)); // TODO-AB -- Change that at some point

	//------------------------------------------------
	// STEP 2 - Create Slate host (aka, the main window for the tool)

	//TAttribute<FText> Label = TAttribute<FText>(this, &FGridEditorToolkit::GetToolkitName);
	//TAttribute<FText> LabelSuffix = TAttribute<FText>(this, &FGridEditorToolkit::GetTabSuffix);

	//TSharedPtr<SDockTab> ToolkitMajorTab;

	//SAssignNew(ToolkitMajorTab, SDockTab)
	//	.ContentPadding(0.f)
	//	.TabRole(MajorTab) // MajorTab is the nickname for Window
	//	// .Tooltip -- TODO-AB
	//	//.IconColor(this, ) -- TODO-AB
	//	.Label(Label)
	//	.LabelSuffix(LabelSuffix);

	//
	//TSharedPtr<FTabManager::FSearchPreference> SearchPreference = MakeShareable(new FTabManager::FLiveTabSearch(TEXT("LevelEditor"))); // AB - Other stuff to do to set the last tab
	//FGlobalTabmanager::Get()->InsertNewDocumentTab(TEXT("StandaloneToolkit"), *SearchPreference, ToolkitMajorTab.ToSharedRef());

	//auto Window = ToolkitMajorTab->GetParentWindow();
	//if (Window.IsValid())
	//{
	//	Window->BringToFront(); // Bring new window to front
	//}

	////------------------------------------------------
	//// STEP 3 - Get the new TabManager

	//// Set persistence
	//ToolkitTabManager = FGlobalTabmanager::Get()->NewTabManager(ToolkitMajorTab.ToSharedRef()); // create the tab manager for this window
	//ToolkitTabManager->SetOnPersistLayout(FTabManager::FOnPersistLayout::CreateRaw(this, &FGridEditorToolkit::OnPersistLayout));
	//ToolkitTabManager->SetAllowWindowMenuBar(true);

	//// STEP 4 - Set content
	//
	//// Set tab content (aka the Toolkit host)
	//ToolkitMajorTab->SetContent
	//(
	//	SAssignNew(ToolkitHost, SGridEditorToolkitHost, ToolkitTabManager, "GridEditor")
	//);

	//ToolkitManager.RegisterNewToolkit(SharedThis(this)); // TODO-AB - unregister at some point

	//// STEP 5 - Register actions
	//// ToolkitCommands are my command (of this toolkit)

	//ToolkitCommands->MapAction( // TODO-AB - delete this
	//	FGlobalEditorCommonCommands::Get().FindInContentBrowser,
	//	FExecuteAction::CreateSPLambda(this, []()
	//								   {
	//									   UE_LOG(LogTemp, Warning, TEXT("HIT!!!!!!"));
	//								   }));

	//FGlobalEditorCommonCommands::MapActions(ToolkitCommands); // Map generic UE actions

	//// STEP 6 - Create menus
	//AddMenuExtender(GetSharedMenuExtensibilityManager()->GetAllExtenders(ToolkitCommands, {}));

	TSharedRef<FTabManager::FLayout> DefaultLayout = FTabManager::NewLayout("Standalone_GridEditor_Layout_v1")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Horizontal)
			->Split
			(
				FTabManager::NewSplitter()
				->SetOrientation(Orient_Horizontal)
				//->SetSizeCoefficient(1.f)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.8f)
					->SetHideTabWell(true)
					->AddTab(TEXT("Viewport"), ETabState::OpenedTab)
				)
				->Split
				(
					FTabManager::NewSplitter()
					->SetSizeCoefficient(0.2f)
					->SetOrientation(Orient_Vertical)
					->Split
					(
						FTabManager::NewStack()
						->SetSizeCoefficient(0.3f)
						->SetHideTabWell(true)
						->AddTab(TEXT("Browser"), ETabState::OpenedTab)
					)
					->Split
					(
						FTabManager::NewStack()
						->SetSizeCoefficient(0.7f)
						->SetHideTabWell(true)
						->AddTab(TEXT("Details"), ETabState::OpenedTab)
					)
				)
			)
		);

	TArray<UObject*> asdf;
	{
		FAssetEditorToolkit::InitAssetEditor(EToolkitMode::Standalone, nullptr, "NormalDistributionEditor", DefaultLayout, true, true, asdf);
	}
	//TSharedRef<FTabManager::FLayout> Layout = FLayoutSaveRestore::LoadFromConfig(GEditorLayoutIni, DefaultLayout);

	//// host set initial content
	//GetGetEditorToolkitHost()->SetupInitialContent(Layout, ToolkitMajorTab);
	


	// Set Toolbar
	//if (!SharedExtensibilityManager.IsValid())
	//{
	//	SharedExtensibilityManager = MakeShareable(new FExtensibilityManager());
	//}
	//ToolbarExtender.AddUnique(SharedExtensibilityManager->GetAllExtenders(ToolkitCommands, {})); // 
	//
	//TSharedPtr<FExtender> CombinedExtender = FExtender::Combine(ToolbarExtender); // Combine all in one extender
	//UToolMenus* ToolMenus = UToolMenus::Get();
	//UToolMenu* FoundMenu = ToolMenus->FindMenu(DefaultToolbarName);
	//if (!FoundMenu || !FoundMenu->IsRegistered())
	//{
	//	FoundMenu = ToolMenus->RegisterMenu(DefaultToolbarName, NAME_None, EMultiBoxType::SlimHorizontalToolBar);
	//}

	//FToolMenuContext MenuContext(ToolkitCommands, CombinedExtender); // Do I need that?

	// Set Menus


	//const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("GridEditorLayout")

	// STEP X - Overwrite inputs listening in the Toolkit host
	//			if this is not done, the widget will never receive the inputs
	//			also, if we are going to use Mode, it should be handled in the input listener also
}

void FGridEditorToolkitSimple::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(INVTEXT("Grid Editor Window Simple"));

	InTabManager->RegisterTabSpawner("ViewportTab", FOnSpawnTab::CreateLambda([=](const FSpawnTabArgs&)
																			  {
																				  return SNew(SDockTab)
																					  [
																						  SNew(SGridEditorWidget)
																					  ];
																			  })).SetDisplayName(INVTEXT("Viewport"))
																				 .SetGroup(WorkspaceMenuCategory.ToSharedRef());

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs DetailsViewArgs;

	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
	TSharedRef<IDetailsView> DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);

	InTabManager->RegisterTabSpawner("DetailsTab", FOnSpawnTab::CreateLambda([=](const FSpawnTabArgs&)
																			{
																				return SNew(SDockTab)
																					[
																						DetailsView
																					];
																			})).SetDisplayName(INVTEXT("Details"))
																			   .SetGroup(WorkspaceMenuCategory.ToSharedRef());

}

void FGridEditorToolkitSimple::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	InTabManager->UnregisterTabSpawner("ViewportTab");
	InTabManager->UnregisterTabSpawner("DetailsTab");
}

FText FGridEditorToolkitSimple::GetToolkitToolTipText() const
{
	return INVTEXT("Helper Window to Visualize a Game Grid");
}

bool FGridEditorToolkitSimple::IsAssetEditor() const
{
	return false;
}

const TArray<UObject*>* FGridEditorToolkitSimple::GetObjectsCurrentlyBeingEdited() const
{
	// TODO-AB revisit that when we have the actual assets
	static TArray<TObjectPtr<UObject>> EditingObjects2;
	return &ObjectPtrDecay(EditingObjects2);
}

void FGridEditorToolkitSimple::OnPersistLayout(const TSharedRef<FTabManager::FLayout>& Layout)
{
	if (FUnrealEdMisc::Get().IsSavingLayoutOnClosedAllowed())
	{
		FLayoutSaveRestore::SaveToConfig(GEditorLayoutIni, Layout);
	}
}

UE_ENABLE_OPTIMIZATION