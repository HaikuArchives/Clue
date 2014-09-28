//CLVListItem source file


//******************************************************************************************************
//**** PROJECT HEADER FILES
//******************************************************************************************************
#ifndef _BITMAP_H
#include <Bitmap.h>
#endif

#ifndef _PATH_H
#include <Path.h>
#endif

#ifndef _POINT_H
#include <Point.h>
#endif

#ifndef _REGION_H
#include <Region.h>
#endif

#ifndef _STDIO_H_
#include <stdio.h>
#endif

#ifndef _STRING_H_
#include <string.h>
#endif

#ifndef _VIEW_H
#include <View.h>
#endif


//******************************************************************************************************
//**** PROJECT HEADER FILES
//******************************************************************************************************
#ifndef _CLV_LIST_ITEM_H_
#include "CLVListItem.h"
#endif

#ifndef _CLV_COLUMN_LIST_VIEW_H_
#include "ColumnListView.h"
#endif

#ifndef _CLV_COLUMN_H_
#include "CLVColumn.h"
#endif



/******************************************************************************************************
CLVItem constructor
team_id, char *, BView *, BBitmap *, char *
*******************************************************************************************************/
CLVListItem :: CLVListItem
	(
	uint32 level
,	bool expanded
	)
:	BListItem () //level, expanded)
{
}


/******************************************************************************************************
CLVItem destructor
*******************************************************************************************************/
CLVListItem :: ~CLVListItem
	(
	void
	)
{
}


/******************************************************************************************************
*******************************************************************************************************/
void
CLVListItem :: DrawItem
	(
	BView * owner
,	BRect itemRect
,	bool complete
	)
{
	BList * DisplayList (&((ColumnListView *) owner)->fColumnDisplayList);
	int32 NumberOfColumns (DisplayList->CountItems());
	float PushMax (itemRect.right);
	CLVColumn * ThisColumn (NULL);
	BRect ThisColumnRect (itemRect);
	float ExpanderDelta (OutlineLevel() * 20.0);
	//Figure out what the limit is for expanders pushing other columns
	for (int32 Counter = 0; Counter < NumberOfColumns; Counter++)
	{
		ThisColumn = (CLVColumn *) DisplayList->ItemAt (Counter);
		if ((ThisColumn->fFlags & CLV_EXPANDER) || ThisColumn->fPushedByExpander)
		{
			PushMax = ThisColumn->fColumnEnd;
		}
	}
	BRegion ClippingRegion;
	if (!complete)
	{
		owner->GetClippingRegion (&ClippingRegion);
	}
	else
	{
		ClippingRegion.Set (itemRect);
	}

	float LastColumnEnd (-1.0);

	//Draw the columns
	for (int32 Counter (0); Counter < NumberOfColumns; Counter++)
	{
		ThisColumn = (CLVColumn *) DisplayList->ItemAt (Counter);
		if (!ThisColumn->IsShown ())
		{
			continue;
		}

		ThisColumnRect.left = ThisColumn->fColumnBegin;
		ThisColumnRect.right = LastColumnEnd = ThisColumn->fColumnEnd;
		float Shift (0.0);
		if ((ThisColumn->fFlags & CLV_EXPANDER) || ThisColumn->fPushedByExpander)
			Shift = ExpanderDelta;
		if (ThisColumn->fFlags & CLV_EXPANDER)
		{
			ThisColumnRect.right += Shift;
			if (ThisColumnRect.right > PushMax)
				ThisColumnRect.right = PushMax;
			fExpanderColumnRect = ThisColumnRect;
			if (ClippingRegion.Intersects (ThisColumnRect))
			{
				//Give the programmer a chance to do his kind of highlighting if the item is selected
				DrawItemColumn (owner, ThisColumnRect,
								((ColumnListView *) owner)->fColumnList.IndexOf (ThisColumn),complete);
			}
		}
		else
		{
			ThisColumnRect.left += Shift;
			ThisColumnRect.right += Shift;
			if (Shift > 0.0 && ThisColumnRect.right > PushMax)
				ThisColumnRect.right = PushMax;
			if (ThisColumnRect.right >= ThisColumnRect.left && ClippingRegion.Intersects (ThisColumnRect))
				DrawItemColumn (owner, ThisColumnRect,
					((ColumnListView*)owner)->fColumnList.IndexOf(ThisColumn), complete);
		}
	}
	//Fill the area after all the columns (so the select highlight goes all the way across)
	ThisColumnRect.left = LastColumnEnd + 1.0;
	ThisColumnRect.right = owner->Bounds().right;
	if (ThisColumnRect.left <= ThisColumnRect.right && ClippingRegion.Intersects (ThisColumnRect))
		DrawItemColumn(owner, ThisColumnRect,-1,complete);
}


/******************************************************************************************************
*******************************************************************************************************/
BRect
CLVListItem :: ItemColumnFrame
	(
	int32 column_index
,	ColumnListView * owner
	)
{
	BRect itemRect (owner->ItemFrame (owner->IndexOf (this)));
	float PushMax (itemRect.right);

	//Figure out what the limit is for expanders pushing other columns
	BList* DisplayList (&owner->fColumnDisplayList);
	int32 NumberOfColumns (DisplayList->CountItems());
	CLVColumn * ThisColumn ((CLVColumn *) DisplayList->ItemAt (column_index));

	if(!ThisColumn->IsShown())
	{
		return BRect(-1,-1,-1,-1);
	}

	for (int32 Counter = 0; Counter < NumberOfColumns; Counter++)
	{
		ThisColumn = (CLVColumn*)DisplayList->ItemAt(Counter);
		if((ThisColumn->fFlags & CLV_EXPANDER) || ThisColumn->fPushedByExpander)
			PushMax = ThisColumn->fColumnEnd;
	}

	BRect ThisColumnRect (itemRect);
	ThisColumn = owner->ColumnAt(column_index);
	ThisColumnRect.left = ThisColumn->fColumnBegin;
	ThisColumnRect.right = ThisColumn->fColumnEnd;

	if (ThisColumn->fFlags & CLV_EXPANDER)
	{
		ThisColumnRect.right += OutlineLevel () * 20.0;
		if (ThisColumnRect.right > PushMax)
		{
			ThisColumnRect.right = PushMax;
		}
	}
	else
	{
		if (ThisColumn->fPushedByExpander)
		{
			float Shift (OutlineLevel() * 20.0);
			ThisColumnRect.left += Shift;
			ThisColumnRect.right += Shift;
			if (Shift > 0.0 && ThisColumnRect.right > PushMax)
			{
				ThisColumnRect.right = PushMax;
			}
		}
	}

	if (ThisColumnRect.right >= ThisColumnRect.left)
	{
		return ThisColumnRect;
	}
	else
	{
		return BRect(-1,-1,-1,-1);
	}
}


/******************************************************************************************************
*******************************************************************************************************/
void
CLVListItem :: Update
	(
	BView * owner
,	const BFont * font
	)
{
	BListItem::Update (owner, font);
	if (Height () < 17.0)
	{
		SetHeight (17.0);
	}
	font_height FontAttributes;
	be_plain_font->GetHeight (&FontAttributes);
	float FontHeight = ceil (FontAttributes.ascent) + ceil (FontAttributes.descent);
	fTextOffset = ceil (FontAttributes.ascent) + (Height () - FontHeight) / 2.0;
}


/******************************************************************************************************
*******************************************************************************************************/
void
CLVListItem :: ColumnWidthChanged
	(
	int32 column_index
,	float column_width
,	ColumnListView * the_view
	)
{
	//Get rid of a warning
	column_index = 0;
	column_width = 0;
	the_view = NULL;
}


/******************************************************************************************************
*******************************************************************************************************/
void
CLVListItem :: FrameChanged
	(int32 column_index
,	BRect new_frame
,	ColumnListView * the_view
	)
{
	//Get rid of a warning
	column_index = 0;
	new_frame.left = 0;
	the_view = NULL;

}

