//CLVListItem source file


//******************************************************************************************************
//**** PROJECT HEADER FILES
//******************************************************************************************************
//#define DEBUG 1
#define ADD_IN_FRONT_OF_LIST 1

#ifndef _APP_FILE_INFO_H
#include <AppFileInfo.h>
#endif

#ifndef _BITMAP_H
#include <Bitmap.h>
#endif

#ifndef _BUTTON_H
#include <Button.h>
#endif

#ifndef _DEBUG_H
#include <Debug.h>
#endif

#ifndef _ENTRY_H
#include <Entry.h>
#endif

#ifndef _MESSAGE_H
#include <Message.h>
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

#ifndef _ROSTER_H
#include <Roster.h>
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

#ifndef _TYPE_CONSTANTS_H
#include <TypeConstants.h>
#endif

#ifndef DRAGMESSAGEITEM_H_
#include "DragMessageItem.h"
#endif

#ifndef _CLV_COLUMN_LIST_VIEW_H_
#include "ColumnListView.h"
#endif

#ifndef _CLV_COLUMN_H_
#include "CLVColumn.h"
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif

const float LEFT_BUFFER = 4.0f;

/******************************************************************************************************
CTeamItem constructor
*******************************************************************************************************/
DragMessageItem :: DragMessageItem
(
	const BMessage* message
	,	const char* name
	,	type_code type
	,	int32 count
)
	:	CLVListItem()
	,	m_name(name)
	,	m_type(type)
	,	m_count(count)
	,	m_message(message)
{
//	char * name;
//	if (B_OK == m_message->GetInfo (B_ANY_TYPE, index, &name, &m_tc, &m_count))
//	{
//		m_entry = name;
//	}
}


/******************************************************************************************************
CLVItem destructor
*******************************************************************************************************/
DragMessageItem :: ~DragMessageItem
(
	void
)
{
}


/******************************************************************************************************
column_index (0-N) is based on the order in which the columns were added
to the ColumnListView, not the display order.  An index of -1 indicates
that the program needs to draw a blank area beyond the last column.  The
main purpose is to allow the highlighting bar to continue all the way to
the end of the ColumnListView, even after the end of the last column.
*******************************************************************************************************/
void
DragMessageItem :: DrawItemColumn
(
	BView* owner
	,	BRect item_column_rect
	,	int32 column_index
	,	bool complete
)
{
	rgb_color color;
	bool selected(IsSelected());
	if (selected)
		color = CLR_LIST_SELECTED_GREY;
	else
		color = CLR_WHITE;
	owner->SetLowColor(color);
	owner->SetDrawingMode(B_OP_COPY);
	if (selected || complete) {
		owner->SetHighColor(color);
		owner->FillRect(item_column_rect);
	}
	BRegion Region;
	Region.Include(item_column_rect);
	owner->ConstrainClippingRegion(&Region);
	owner->SetHighColor(Black);

	//possible columns 0 - ?
	switch (column_index) {
		case 0: //Visible
			owner->DrawString(m_name.String(), BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
			break;
		case 1: //small icon
			switch (m_type) {
				case B_ANY_TYPE:
					owner->DrawString("B_ANY_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_BOOL_TYPE:
					owner->DrawString("B_BOOL_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_CHAR_TYPE:
					owner->DrawString("B_CHAR_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_COLOR_8_BIT_TYPE:
					owner->DrawString("B_COLOR_8_BIT_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_DOUBLE_TYPE:
					owner->DrawString("B_DOUBLE_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_FLOAT_TYPE:
					owner->DrawString("B_FLOAT_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_GRAYSCALE_8_BIT_TYPE:
					owner->DrawString("B_GRAYSCALE_8_BIT_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_INT64_TYPE:
					owner->DrawString("B_INT64_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_INT32_TYPE:
					owner->DrawString("B_INT32_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_INT16_TYPE:
					owner->DrawString("B_INT16_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_INT8_TYPE:
					owner->DrawString("B_INT8_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_MESSAGE_TYPE:
					owner->DrawString("B_MESSAGE_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_MESSENGER_TYPE:
					owner->DrawString("B_MESSENGER_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_MIME_TYPE:
					owner->DrawString("B_MIME_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_MONOCHROME_1_BIT_TYPE:
					owner->DrawString("B_MONOCHROME_1_BIT_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_OBJECT_TYPE:
					owner->DrawString("B_OBJECT_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_OFF_T_TYPE:
					owner->DrawString("B_OFF_T_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_PATTERN_TYPE:
					owner->DrawString("B_PATTERN_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_POINTER_TYPE:
					owner->DrawString("B_POINTER_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_POINT_TYPE:
					owner->DrawString("B_POINT_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_RAW_TYPE:
					owner->DrawString("B_RAW_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_RECT_TYPE:
					owner->DrawString("B_RECT_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_REF_TYPE:
					owner->DrawString("B_REF_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_RGB_32_BIT_TYPE:
					owner->DrawString("B_RGB_32_BIT_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_RGB_COLOR_TYPE:
					owner->DrawString("B_RGB_COLOR_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_SIZE_T_TYPE:
					owner->DrawString("B_SIZE_T_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_SSIZE_T_TYPE:
					owner->DrawString("B_SSIZE_T_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_STRING_TYPE:
					owner->DrawString("B_STRING_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_TIME_TYPE:
					owner->DrawString("B_TIME_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_UINT64_TYPE:
					owner->DrawString("B_UINT64_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_UINT32_TYPE:
					owner->DrawString("B_UINT32_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_UINT16_TYPE:
					owner->DrawString("B_UINT16_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_UINT8_TYPE:
					owner->DrawString("B_UINT8_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_MEDIA_PARAMETER_TYPE:
					owner->DrawString("B_MEDIA_PARAMETER_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_MEDIA_PARAMETER_WEB_TYPE:
					owner->DrawString("B_MEDIA_PARAMETER_WEB_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_MEDIA_PARAMETER_GROUP_TYPE:
					owner->DrawString("B_MEDIA_PARAMETER_GROUP_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_ATOM_TYPE:
					owner->DrawString("B_ATOM_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_ATOMREF_TYPE:
					owner->DrawString("B_ATOMREF_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				case B_ASCII_TYPE:
					owner->DrawString("B_ASCII_TYPE", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					break;
				default: {
						char tmpstr[7];
						sprintf(tmpstr, "'%c%c%c%c'", (char) m_type >> 24, (char) m_type >> 16, (char) m_type >> 8, (char) m_type);
						owner->DrawString(tmpstr, BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
					}
					break;
			}
			break;
		case 2: { //Count
				char tmpstr[7];
				sprintf(tmpstr, "%li", m_count);
				owner->DrawString(tmpstr, BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
			}
			break;
		case 3: { //Size
				char tmpstr[7];
				sprintf(tmpstr, "%li", m_count);
				owner->DrawString(tmpstr, BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
			}
			break;
		case 4: //Data
			owner->DrawString("Data", BPoint(item_column_rect.left + LEFT_BUFFER, item_column_rect.top + fTextOffset));
			break;
	}
	owner->ConstrainClippingRegion(NULL);
}


void
DragMessageItem :: Update
(
	BView* owner
	,	const BFont* font
)
{
	BListItem::Update(owner, font);
	SetHeight(m_count * Height());

	font_height FontAttributes;
	be_plain_font->GetHeight(&FontAttributes);
	fTextOffset = ceil(FontAttributes.ascent) + ceil(FontAttributes.leading);
	//float FontHeight = ceil (FontAttributes.ascent) + ceil (FontAttributes.descent);
	//fTextOffset = ceil (FontAttributes.ascent) + (Height () - FontHeight) / 2.0;
}


