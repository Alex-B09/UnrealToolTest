// Grid Tool Personal Project - AB - 04-2024

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SLeafWidget.h"



DECLARE_DELEGATE_OneParam(FOnMeanChanged, float /*Test*/)

/**
 * 
 */
class SGridEditorWidget : public SLeafWidget
{
public:
	SLATE_BEGIN_ARGS(SGridEditorWidget)
		: _Test1(0.5f)
		{}
		SLATE_ATTRIBUTE(float, Test1)
		SLATE_EVENT(FOnMeanChanged, OnMeanChanged)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	FVector2D ComputeDesiredSize(float) const override;

	TAttribute<float> Test1;
	FOnMeanChanged OnMeanChanged;
};
