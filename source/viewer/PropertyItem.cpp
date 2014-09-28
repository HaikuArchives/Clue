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

#ifndef _STDIO_H
#include <stdio.h>
#endif

#ifndef _STRING_H
#include <string.h>
#endif

#ifndef _VIEW_H
#include <View.h>
#endif

#ifndef CLUE_H
#define CLUE
#define BUILD_CLUE_APPLICATION = 1
#include "Clue.h"
#endif

#ifndef _CLUE_PROPERTYITEM_H_
#include "PropertyItem.h"
#endif

#ifndef _CLV_LIST_ITEM_H_
#include "CLVListItem.h"
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif

extern BBitmap * g_bmpEvents[];
extern BBitmap * g_OtherBmps[];

typedef struct
{
	ClueEvent		Event;
	char			Type[30];
	BBitmap *		Bmp;
	const char *	Description;
} ItemInfo;

static ItemInfo g_ItemInfo[] =
{
{CE_BIRTH,		"CE_BIRTH",		NULL, STR_CT_CLASS_BIRTH_DESCRIPTION},
{CE_DEATH,		"CE_DEATH",		NULL, STR_CT_CLASS_DEATH_DESCRIPTION},
{CE_ENTER,		"CE_ENTER",		NULL, STR_CT_METHOD_ENTER_DESCRIPTION},
{CE_EXIT,		"CE_EXIT",		NULL, STR_CT_METHOD_EXIT_DESCRIPTION},
{CE_OK,			"CE_OK",		NULL, STR_CT_OK_DESCRIPTION},
{CE_INFO,		"CE_INFO",		NULL, STR_CT_INFO_DESCRIPTION},
{CE_WARNING,	"CE_WARNING",	NULL, STR_CT_WARNING_DESCRIPTION},
{CE_ERROR,		"CE_ERROR", 	NULL, STR_CT_ERROR_DESCRIPTION},
{CE_SUCCEEDED,	"CE_SUCCEEDED",	NULL, STR_CT_AUDIT_SUCCESS_DESCRIPTION},
{CE_FAILED,		"CE_FAILED",	NULL, STR_CT_AUDIT_FAILURE_DESCRIPTION},
{CE_TIMER,		"CE_TIMER",		NULL, STR_CT_TIMER_DESCRIPTION},
{CE_OBJECT,		"CE_OBJECT",	NULL, STR_CT_OBJECT_DESCRIPTION}
};

/******************************************************************************************************
CLVItem constructor
team_id, char *, BView *, BBitmap *, char *
*******************************************************************************************************/
PropertyItem :: PropertyItem
	(
	uint32 ClueInfoIndex
	)
:	CLVListItem ()
,	m_ClueInfoIndex (ClueInfoIndex)
,	m_Event (g_ItemInfo[ClueInfoIndex].Event)
,	m_selected (false)
{
	g_ItemInfo[m_ClueInfoIndex].Bmp = g_bmpEvents[m_ClueInfoIndex];
}


/******************************************************************************************************
*******************************************************************************************************/
void
PropertyItem :: DrawItemColumn
	(
	BView * owner
,	BRect item_column_rect
,	int32 column_index
,	bool complete
	)
{
	bool selected (IsSelected());
	rgb_color color (selected ? CLR_LIST_SELECTED_GREY : CLR_WHITE);
//	color = IsSelected() ? CLR_LIST_SELECTED_GREY : CLR_WHITE;
//	if (selected)
//	{
//		color = CLR_LIST_SELECTED_GREY;
//	}
//	else
//	{
//		color = CLR_WHITE;
//	}

	owner->SetLowColor (color);
	owner->SetDrawingMode (B_OP_COPY);
	if (selected || complete)
	{
		owner->SetHighColor (color);
		owner->FillRect (item_column_rect);
	}
	BRegion Region (item_column_rect);
//	Region.Include (item_column_rect);
	owner->ConstrainClippingRegion (&Region);
	owner->SetHighColor (0, 0, 0, 255);

	//possible columns 0 - 3
	switch (column_index)
	{
		case 0: //Selected
			if (m_selected)
			{
				BPoint pt (item_column_rect.left + 4.0f, (item_column_rect.bottom - item_column_rect.top) / 2.0f - 3.0f + item_column_rect.top);
				owner->SetDrawingMode (B_OP_OVER);
				owner->DrawBitmap (g_OtherBmps[0], pt);
				owner->SetDrawingMode (B_OP_COPY);
			}
			break;
		case 1:
			if (g_ItemInfo[m_ClueInfoIndex].Bmp)
			{
				item_column_rect.left += 2.0f;
				item_column_rect.right = item_column_rect.left + 15.0f;
				item_column_rect.top += 1.0f;
				if (Height () > 20.0f)
				{
					item_column_rect.top += ceil((Height () - 20.0f) / 2.0f);
				}
				item_column_rect.bottom = item_column_rect.top + 15.0f;
				owner->SetDrawingMode (B_OP_OVER);
				owner->DrawBitmap (g_ItemInfo[m_ClueInfoIndex].Bmp, BRect (0.0f, 0.0f, 15.0f, 15.0f), item_column_rect);
				owner->SetDrawingMode (B_OP_COPY);
			}
			break;
		case 2:
			owner->DrawString (g_ItemInfo[m_ClueInfoIndex].Description, BPoint (item_column_rect.left + 4.0f, item_column_rect.top + fTextOffset));
			break;
		case 3:
			owner->DrawString (g_ItemInfo[m_ClueInfoIndex].Type, BPoint (item_column_rect.left + 4.0f, item_column_rect.top + fTextOffset));
			break;
	}
	owner->ConstrainClippingRegion (NULL);
}


/******************************************************************************************************
*******************************************************************************************************/
void
PropertyItem :: Update
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
PropertyItem :: SetFilter
	(
	uint32 flags
)
{
}


/******************************************************************************************************
*******************************************************************************************************/
uint32
PropertyItem :: Filter
	(
	void
	)
{
	return (0);
}

