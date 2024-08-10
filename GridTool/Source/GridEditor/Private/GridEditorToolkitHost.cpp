// Grid Tool Personal Project - AB - 04-2024


#include "GridEditorToolkitHost.h"
#include "Widgets/SWidget.h"

void SGridEditorToolkitHost::Construct(const FArguments& InArgs, const TSharedPtr<FTabManager>& InTabManager, const FName InitAppName)
{
	static int UniqueID = 0;

	AppName = InitAppName;
	StatusBarName = FName(AppName, UniqueID);
	++UniqueID;

	HostToolkitTabManager = InTabManager;

	EditorCloseRequest = InArgs._OnRequestClose;
	EditorClosing = InArgs._OnClose;
}

TSharedRef<SWidget> SGridEditorToolkitHost::GetParentWidget()
{
	return AsShared();
}

void SGridEditorToolkitHost::BringToFront()
{
	if (TSharedPtr<SDockTab> Host = HostTab.Pin(); Host.IsValid())
	{
		TSharedPtr<SWindow> ParentWindow = Host->GetParentWindow();
		if (ParentWindow.IsValid() && !ParentWindow->IsActive())
		{
			ParentWindow->BringToFront();
		}
	}

	FGlobalTabmanager::Get()->DrawAttentionToTabManager(HostToolkitTabManager.ToSharedRef());
}

TSharedPtr<FTabManager> SGridEditorToolkitHost::GetTabManager() const
{
	return HostToolkitTabManager;
}

void SGridEditorToolkitHost::OnToolkitHostingStarted(const TSharedRef<class IToolkit>& Toolkit)
{
	HostedToolkit = Toolkit;
}

void SGridEditorToolkitHost::OnToolkitHostingFinished(const TSharedRef<class IToolkit>& Toolkit)
{
	if (HostedToolkit == Toolkit)
	{
		HostedToolkit = nullptr;
	}
}

UWorld* SGridEditorToolkitHost::GetWorld() const
{
	// Not world centric, no need to keep world
	return NULL;
}

FEditorModeTools& SGridEditorToolkitHost::GetEditorModeManager() const
{
	check(HostedToolkit.IsValid()); // we need this to be valid
	return HostedToolkit->GetEditorModeManager();
}

UTypedElementCommonActions* SGridEditorToolkitHost::GetCommonActions() const
{
	return nullptr;
}

FName SGridEditorToolkitHost::GetStatusBarName() const
{
	return StatusBarName;
}

FReply SGridEditorToolkitHost::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	if (FSlateApplication::Get().IsNormalExecution())
	{

		// TODO-AB Here I should check for editor mode
		if (HostedToolkit.IsValid())
		{
			if (HostedToolkit->ProcessCommandBindings(InKeyEvent))
			{
				return FReply::Handled();
			}
		}
	}

	return SCompoundWidget::OnKeyDown(MyGeometry, InKeyEvent);
}

void SGridEditorToolkitHost::SetupInitialContent(const TSharedPtr<FTabManager::FLayout> Layout, const TSharedPtr<SDockTab>& InHostTab)
{
	// STEP 1 - Get Menu Name
	//			This will be use for registering the menu with Unreal
	FName MenuAppName = "GridEditor.MainMenu";



	// STEP 2 - Register+Create menu bar
	//			for that, we can ask the toolkit to generate a list of things to show
	//			We can also ask the modes to do that
	UToolMenu* Menu = UToolMenus::Get()->RegisterMenu(MenuAppName, "MainFrame.MainMenu");
	//CreateDefaultStandaloneMenuBar(Menu);

	// STEP 3 - Set Layout
	//RestoreFromLayout(Layout);

	HostTab = InHostTab;
	InHostTab->SetCanCloseTab(EditorCloseRequest);
	//InHostTab->SetOnTabClosed(......) TODO_AB
	ChildSlot[SNullWidget::NullWidget];
	HostToolkitTabManager->CloseAllAreas();

	TSharedPtr<SWindow> ParentWindow = FSlateApplication::Get().FindWidgetWindow(InHostTab->AsShared());
	TSharedPtr<SWidget> RestoredUI = HostToolkitTabManager->RestoreFrom(Layout->AsShared(), ParentWindow);



	// STEP 4 - Create Toolbar
	//			same as before but with toolbar

	// STEP 5 - Generate Menus

	// STEP 6 - Set Host content
}
