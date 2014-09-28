//#define DEBUG 1

#ifndef _BITMAP_H
#include <Bitmap.h>
#endif

#ifndef _DEBUG_H
#include <Debug.h>
#endif

#ifndef _GRAPHICS_DEFS_H
#include <GraphicsDefs.h>
#endif

#ifndef _INTERFACE_DEFS_H
#include "InterfaceDefs.h"
#endif

#ifndef _POINT_H
#include <Point.h>
#endif

#ifndef _REGION_H
#include <Region.h>
#endif

#ifndef _VIEW_H
#include <View.h>
#endif

#ifndef _OBJECTFILTER_ITEM_H
#include "ObjectFilterItem.h"
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif

#ifndef _CLUE_AREA_MANAGER_H
#include "ClueAreaManager.h"
#endif

//#ifndef _CAM_CONSTANTS_H
//#include "CAM_Constants.h"
//#endif

//the one and only instance of a ClueAreaManager, already defined in LiveView
extern ClueAreaManager CAM;
extern BBitmap * g_OtherBmps[];



ObjectFilterItem :: ObjectFilterItem
	(
	const char * inText
,	bool IsLeafNode
,	uint32 inIndex
,	uint32 inMask
,	bool ControlsSubItems
,	uint32 inOutlineLevel
,	bool inExpanded
	)
:	BListItem (inOutlineLevel, inExpanded)
,	m_Index (inIndex)
,	m_Mask (inMask)
,	m_Text (inText)
,	m_IsLeafNode (IsLeafNode)
,	m_GrayedOut (false)
,	m_ControlsSubItems (ControlsSubItems)
{
}


ObjectFilterItem :: ~ObjectFilterItem
	(
	void
	)
{
}

void
ObjectFilterItem :: DrawItem
	(
	BView * owner
,	BRect bounds
,	bool complete
	)
{
	rgb_color color;
	rgb_color textcolor;
	bool selected (IsSelected());
	if (selected)
	{
		textcolor = CLR_LIST_SELECTED_TEXT;
		color = CLR_LIST_SELECTED_BACKGROUND;
//		color = CLR_LIST_SELECTED_GREY;
	}
	else
	{
		textcolor = CLR_LIST_TEXT;
		color = CLR_LIST_BACKGROUND;
//		color = CLR_WHITE;
	}
	owner->SetLowColor (color);
	owner->SetDrawingMode (B_OP_COPY);
	if (selected || complete)
	{
		owner->SetHighColor (color);
		owner->FillRect (bounds);
	}
//	BRegion Region;
//	Region.Include (bounds);
//	owner->ConstrainClippingRegion (&Region);
	if (m_GrayedOut)
	{
		textcolor = tint_color (textcolor, B_LIGHTEN_2_TINT);
	}
	owner->SetHighColor (textcolor);


//	const char * pText (Text ());
//	((BListItem *)this)->DrawItem (owner, bounds, complete);
//	float indent (OutlineLevel () * 20.0f);
	font_height FontAttributes;
	owner->GetFontHeight (&FontAttributes);
	float FontHeight = ceil (FontAttributes.ascent) + ceil (FontAttributes.descent);
	float fTextOffset = ceil (FontAttributes.ascent) + (bounds.Height () - FontHeight) / 2.0;
//	fTextOffset = ceil (FontAttributes.ascent) + (Height () - FontHeight) / 2.0;
//	owner->DrawString (pText, BPoint (indent + 12.0f, bounds.top + fTextOffset));
	if (m_Index)
	{
		owner->DrawString (m_Text.String (), BPoint (bounds.left + 12.0f, bounds.top + fTextOffset));
	}
	else
	{
		owner->DrawString (m_Text.String (), BPoint (bounds.left + 4.0f, bounds.top + fTextOffset));
	}


	if (m_Index)
	{
		float h (bounds.Height() / 2.0f - 3.0f);
		owner->SetDrawingMode (B_OP_OVER);
		owner->DrawBitmap (g_OtherBmps[(CAM.m_data->m_mask[m_Index] & m_Mask) ? 1 : 0], BPoint (bounds.left, bounds.top + h));
		owner->SetDrawingMode (B_OP_COPY);
	}
}


void
ObjectFilterItem :: SetChecked
	(
	bool checked
	)
{
	//m_Checked = checked;
	if (checked)
		CAM.m_data->m_mask[m_Index] = CAM.m_data->m_mask[m_Index] | m_Mask;
	else
		CAM.m_data->m_mask[m_Index] = CAM.m_data->m_mask[m_Index] & ~m_Mask;
}


bool
ObjectFilterItem :: IsChecked
	(
	void
	)
{
	return CAM.m_data->m_mask[m_Index] & m_Mask;
	//return m_Checked;
}


bool
ObjectFilterItem :: ToggleChecked
	(
	void
	)
{
	if (CAM.m_data->m_mask[m_Index] & m_Mask) //(m_Checked)
	{
		//m_Checked = false;
		CAM.m_data->m_mask[m_Index] = CAM.m_data->m_mask[m_Index] & ~m_Mask;
	}
	else
	{
		CAM.m_data->m_mask[m_Index] = CAM.m_data->m_mask[m_Index] | m_Mask;
//		m_Checked = true;
	}

	return (CAM.m_data->m_mask[m_Index] & m_Mask) ? true : false;
}


bool
ObjectFilterItem :: IsLeafNode
	(
	void
	)
{
	return m_IsLeafNode;
}

bool
ObjectFilterItem :: ControlsSubItems
	(
	void
	)
{
	return m_ControlsSubItems;
}


void
ObjectFilterItem :: SetGrayed
	(
	bool inValue
	)
{
//	if (m_IsLeafNode)
		m_GrayedOut = inValue;
}



