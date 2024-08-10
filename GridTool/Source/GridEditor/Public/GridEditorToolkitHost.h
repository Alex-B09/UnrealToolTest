// Grid Tool Personal Project - AB - 04-2024

#pragma once

#include "CoreMinimal.h"
#include "Input/Reply.h"
#include "Widgets/SWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"
#include "Framework/Docking/TabManager.h"
#include "Toolkits/IToolkit.h"
#include "Toolkits/IToolkitHost.h"
#include "Toolkits/AssetEditorToolkit.h"

DECLARE_DELEGATE_RetVal(bool, FRequestGridEditorClose);
DECLARE_DELEGATE(FGridEditorClosing);
/**
 * 
 */
class SGridEditorToolkitHost 
	:public IToolkitHost
	,public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SGridEditorToolkitHost) {}
		SLATE_EVENT(FRequestGridEditorClose, OnRequestClose)
		SLATE_EVENT(FGridEditorClosing, OnClose)
	SLATE_END_ARGS()


	void Construct(const FArguments& InArgs, const TSharedPtr<FTabManager>& InTabManager, const FName InitAppName);

	/* IToolkitHost interface START*/
	virtual TSharedRef<class SWidget> GetParentWidget() override;
	virtual void BringToFront() override;
	virtual TSharedPtr<FTabManager> GetTabManager() const override;
	virtual void OnToolkitHostingStarted(const TSharedRef<class IToolkit>& Toolkit) override;
	virtual void OnToolkitHostingFinished(const TSharedRef<class IToolkit>& Toolkit) override;
	virtual class UWorld* GetWorld() const override;
	virtual FEditorModeTools& GetEditorModeManager() const override;
	virtual UTypedElementCommonActions* GetCommonActions() const override;
	virtual FName GetStatusBarName() const override;
	virtual FOnActiveViewportChanged& OnActiveViewportChanged() override { return OnActiveViewportChangedDelegate; }
	/* IToolkitHost interface END*/

	/* SCompoundWidget overrides */
	virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;
	virtual bool SupportsKeyboardFocus() const override { return true; }
	/* SCompoundWidget overrides END */

	TArray<TSharedPtr<FExtender>>& GetMenuExtenders() { return MenuExtenders; }

	void SetupInitialContent(const TSharedPtr<FTabManager::FLayout> Layout, const TSharedPtr<SDockTab>& HostTab);

private:
	class SWidget* ParentWidget;

	TWeakPtr<SDockTab> HostTab;
	TSharedPtr<FTabManager> HostToolkitTabManager;
	TSharedPtr<IToolkit> HostedToolkit;

	TArray<TSharedPtr<FExtender>> MenuExtenders;

	FName AppName;
	FName StatusBarName;

	FRequestGridEditorClose EditorCloseRequest;
	FGridEditorClosing EditorClosing;

	/** A delegate which is called any time the LevelEditor's active viewport changes. */
	FOnActiveViewportChanged OnActiveViewportChangedDelegate;
};
