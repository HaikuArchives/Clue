//#define DEBUG 1

#ifndef _APP_FILE_INFO_H
#include <AppFileInfo.h>
#endif

#ifndef _APPLICATION_H
#include <Application.h>
#endif

#ifndef _BOX_H
#include <Box.h>
#endif

#ifndef _BUTTON_H
#include <Button.h>
#endif

#ifndef _DEBUG_H
#include <Debug.h>
#endif

#ifndef _FILE_H
#include <File.h>
#endif

#ifndef _FONT_H
#include <Font.h>
#endif

#ifndef _MESSAGE_H
#include <Message.h>
#endif

#ifndef _OUTLINE_LIST_VIEW_H
#include <OutlineListView.h>
#endif

#ifndef _POINT_H
#include <Point.h>
#endif

#ifndef _ROSTER_H
#include <Roster.h>
#endif

#ifndef _SCROLL_VIEW_H
#include <ScrollView.h>
#endif

#ifndef _STDIO_H
#include <stdio.h>
#endif

#ifndef _RECT_H
#include <Rect.h>
#endif

#ifndef _REGION_H
#include <Region.h>
#endif

#ifndef _SCROLL_VIEW_H
#include <ScrollView.h>
#endif

#ifndef _TEXTVIEW_H
#include <TextView.h>
#endif

#ifndef _VIEW_H
#include <View.h>
#endif

#ifndef _WINDOW_H
#include <Window.h>
#endif

#ifndef UTILITY_H
#include "Utility.h"
#endif

#ifndef _EDITVIEW_H
#include "EditView.h"
#endif

#ifndef _PREFERENCES_ITEM_H
#include "PreferenceItem.h"
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif



EditView :: EditView
	(
	BRect frame
,	BMessage * message
,	const char * name
,	uint32 resizeFlags
,	uint32 flags
,	border_style border
	)
:	BBox (frame, name, resizeFlags, flags, border)
,	m_Message (message)
{
	ssize_t numBytes (0);
	rgb_color * pColor;

	if (B_OK == m_Message->FindData ("value", B_RGB_COLOR_TYPE, (const void **) &pColor, &numBytes))
	{
		PRINT (("\n\nEditView color: red=%i, green=%i, blue=%i\n\n", pColor->red, pColor->green, pColor->blue));
	}
}


EditView :: ~EditView
	(
	void
	)
{
}


/***************************************************************
***************************************************************/
//bool
//EditBoolView :: Save
//	(
//	void
//	)
//{
//	return true;
//}

