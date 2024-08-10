// Grid Tool Personal Project - AB - 04-2024


#include "GridEditorWidget.h"

void SGridEditorWidget::Construct(const FArguments& InArgs)
{
	Test1 = InArgs._Test1;
	OnMeanChanged = InArgs._OnMeanChanged;
}

int32 SGridEditorWidget::OnPaint(const FPaintArgs& Args, 
								 const FGeometry& AllottedGeometry, 
								 const FSlateRect& MyCullingRect, 
								 FSlateWindowElementList& OutDrawElements, 
								 int32 LayerId, 
								 const FWidgetStyle& InWidgetStyle, 
								 bool bParentEnabled) const
{
	// This is where we build the visual representation of the widget/tab
	return LayerId;
}

FVector2D SGridEditorWidget::ComputeDesiredSize(float) const
{
	return FVector2D(200.0, 200.0);
}
