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

#ifndef _COLOR_CONTROL_H
#include <ColorControl.h>
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

#ifndef _EDITCOLORVIEW_H
#include "EditColorView.h"
#endif

#ifndef _PREFERENCES_ITEM_H
#include "PreferenceItem.h"
#endif

#ifndef _PREFERENCESVIEW_H
#include "PreferencesView.h"
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif

extern BMessage g_Settings;


EditColorView :: EditColorView
(
	BRect frame
	,	BMessage* message
)
	:	EditView(frame, message, "EditColorView", B_FOLLOW_ALL_SIDES)
	,	m_ColorControl(NULL)
	,	m_view(NULL)
{
	SetViewColor(CLR_TOOLBAR_GREY);

	m_ColorControl = new BColorControl(BPoint(10, 20), B_CELLS_32x8, 1, "The Color Control",
									   new BMessage('colr'));
	AddChild(m_ColorControl);
	m_ColorControl->ResizeToPreferred();
	BRect rect(m_ColorControl->Bounds());
	float w(rect.Width());
	rect.top = 30.0f + rect.Height();
	rect.bottom = rect.top + 30.0f;
	rect.left = 10.0f;
	rect.right = rect.left + w;
	m_view = new BView(rect, "shownewcolor", B_FOLLOW_NONE, 0);
	AddChild(m_view);
}


EditColorView :: ~EditColorView
(
	void
)
{
}


/***************************************************************
***************************************************************/
void
EditColorView :: MessageReceived
(
	BMessage* msg
)
{
	switch (msg->what) {
		case 'colr': {
				PreferencesView* PV(dynamic_cast<PreferencesView*>(Parent()));
				m_view->SetViewColor(m_ColorControl->ValueAsColor());
				PV->SetDirty();
				m_view->Invalidate();  //tell it to redraw with new color
			}
			break;
		case B_OBSERVER_NOTICE_CHANGE: {
				uint32 change(0);
				msg->FindInt32(B_OBSERVE_WHAT_CHANGE, (int32*) &change);
				switch (change) {
					case MSG_SETTINGS_CHANGED: {
//				BMessage msgtmp;
//				if (B_OK == g_Settings.FindMessage ("Background Color", &msgtmp))
//				{
//					rgb_color *clr (NULL);
//					ssize_t numBytes (0);
//					if (B_OK == msgtmp.FindData ("value", B_RGB_COLOR_TYPE, (const void **) &clr, &numBytes))
//					{
							SetViewColor(CLR_BACKGROUND);
							SetLowColor(CLR_BACKGROUND);
							Invalidate();
							m_ColorControl->SetViewColor(CLR_BACKGROUND);
							m_ColorControl->SetLowColor(CLR_BACKGROUND);
							m_ColorControl->Invalidate();
							BView* child(NULL);
							child = m_ColorControl->ChildAt(0);
							if (child) {
								child->SetViewColor(CLR_BACKGROUND);
								child->SetLowColor(CLR_BACKGROUND);
								child->Invalidate();
							}
							child = m_ColorControl->ChildAt(1);
							if (child) {
								child->SetViewColor(CLR_BACKGROUND);
								child->SetLowColor(CLR_BACKGROUND);
								child->Invalidate();
							}
							child = m_ColorControl->ChildAt(2);
							if (child) {
								child->SetViewColor(CLR_BACKGROUND);
								child->SetLowColor(CLR_BACKGROUND);
								child->Invalidate();
							}
//					}
//				}
//				else
//				{
//					PRINT (("didn't find setting for Background Color\n"));
//				}
						}
						break;
				}
			}
			break;
		default:
			BView::MessageReceived(msg);
	}
}


/***************************************************************
***************************************************************/
void
EditColorView :: AllAttached(void)
{
	BMessage msg('colr');
	EditView::AllAttached();
	m_ColorControl->SetTarget((BHandler*) this);
	m_ColorControl->SetValue(m_color);
//	m_view->SetViewColor (m_ColorControl->ValueAsColor ());
//	m_view->Invalidate ();
	MessageReceived(&msg);
	BWindow* pwnd(Window());
	if (pwnd)
		((BHandler*)pwnd)->StartWatching((BHandler*) this, MSG_SETTINGS_CHANGED);
}


/******************************************************************************************************
*******************************************************************************************************/
void
EditColorView :: AttachedToWindow
(
	void
)
{
	EditView::AttachedToWindow();
//	m_ColorControl->SetValue (m_color);
//	m_ColorControl->Invalidate ();
//	m_view->SetViewColor (m_ColorControl->ValueAsColor ());
//	m_view->Invalidate ();
//	m_view->SetViewColor (m_ColorControl->ValueAsColor ());
//	m_view->Invalidate (); //tell it to redraw with new color
}


/******************************************************************************************************
*******************************************************************************************************/
void
EditColorView :: DetachedFromWindow
(
	void
)
{
	EditView::DetachedFromWindow();
	BWindow* pwnd(Window());
	if (pwnd)
		((BHandler*)pwnd)->StopWatching((BHandler*) this, MSG_SETTINGS_CHANGED);
}


/******************************************************************************************************
*******************************************************************************************************/
void
EditColorView :: Draw
(
	BRect updateRect
)
{
	EditView::Draw(updateRect);
	BRect rc(m_view->Frame());
	rc.InsetBy(-1.0f, -1.0f);
	StrokeRect(rc);
}


/***************************************************************
***************************************************************/
bool
EditColorView :: Save
(
	void
)
{
	PRINT(("EditColorView::Save\n"));
	m_Message->MakeEmpty();
	rgb_color colorpref = m_ColorControl->ValueAsColor();
	colorpref.alpha = 255;
	m_Message->AddData("value", B_RGB_COLOR_TYPE, &colorpref, sizeof(rgb_color));
	PRINT(("   color: red=%i, green=%i, blue=%i\n", m_color.red, m_color.green, m_color.blue));
	return true;
}

bool
EditColorView :: PopulateData
(
	BMessage* message
)
{
	bool retval(false);
	rgb_color* pColor(NULL);
	ssize_t numBytes(0);

	PRINT(("\n\nEditColorView\n"));

	if (message->FindData("value", B_RGB_COLOR_TYPE, (const void**) &pColor, &numBytes) == B_OK) {
		if (numBytes == sizeof(rgb_color)) {
			memcpy(&m_color, pColor, numBytes);
			PRINT(("   EVC: color: red=%i, green=%i, blue=%i\n", m_color.red, m_color.green, m_color.blue));
			retval = true;
		}
	}

	return retval;
}


/***************************************************************
***************************************************************/
EditColorView*
EditColorView :: Create
(
	BRect frame
	,	BMessage* message
)
{
	EditColorView* pObject(new EditColorView(frame, message));

	if (pObject) {
		if (false == pObject->PopulateData(message)) {
			delete pObject;
			pObject = NULL;
		}
	}

	return pObject;
}








