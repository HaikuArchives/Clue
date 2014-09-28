//#define DEBUG 1

#ifndef _DEBUG_H
#include <Debug.h>
#endif

#ifndef _FONT_H
#include <Font.h>
#endif

#ifndef _MENU_FIELD_H
#include <MenuField.h>
#endif

#ifndef _MENU_ITEM_H
#include <MenuItem.h>
#endif

#ifndef _MESSAGE_H
#include <Message.h>
#endif

#ifndef _POP_UP_MENU_H
#include <PopUpMenu.h>
#endif

#ifndef _RECT_H
#include <Rect.h>
#endif

#ifndef _STRING_VIEW_H
#include <StringView.h>
#endif

#ifndef _STDIO_H_
#include <stdio.h>
#endif

#ifndef _STRING_H_
#include <string.h>
#endif

#ifndef _WINDOW_H
#include <Window.h>
#endif

#ifndef CLUE_H
#define CLUE
#define BUILD_CLUE_APPLICATION = 1
#include "Clue.h"
#endif

#ifndef _EDITTEAMVIEW_H
#include "EditTeamView.h"
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif

#ifndef SLIDER_H
#include "Slider.h"
#endif

#ifndef _TEAMITEM_H_
#include "TeamItem.h"
#endif

#ifndef _BETTER_SCROLL_VIEW_H_
#include "BetterScrollView.h"
#endif

#ifndef _CLV_COLUMN_LIST_VIEW_H_
#include "ColumnListView.h"
#endif

#ifndef _CLV_COLUMN_H_
#include "CLVColumn.h"
#endif

#ifndef _CLUE_PROPERTYITEM_H_
#include "PropertyItem.h"
#endif

extern BMessage g_Settings;


/***************************************************************
***************************************************************/
EditTeamView :: EditTeamView
	(
	BRect frame
,	BMessage * message
	)
:	EditView (frame, message, "EditTeamView", B_FOLLOW_ALL_SIDES)
,	m_slider (NULL)
,	m_bsv (NULL)
,	m_ColumnListView (NULL)
,	m_QueueLength (0)
,	m_OK (NULL)
,	m_CurCat (CC_GENERAL)
,	m_menufld (NULL)
,	m_popupmenu (NULL)
{
	SetViewColor (CLR_TOOLBAR_GREY);

	SetViewColor (CLR_FASHIONABLE);
	m_slider = new Slider (BRect (5.0f, 5.0f, frame.right - 5.0f, 40.0f), "QueueLength", STR_EVENT_QUEUE_LENGTH, NULL, 1, 100000,
		B_TRIANGLE_THUMB, B_FOLLOW_LEFT_RIGHT | B_FOLLOW_TOP);
	rgb_color color = {255, 100, 100, 255};
	m_slider->UseFillColor (true, &color);
	color.red = 155;
	color.green = 155;
	color.blue = 255;
	color.alpha = 255;
	m_slider->SetBarColor (color);
	m_slider->SetHashMarks (B_HASH_MARKS_BOTTOM);
	m_slider->SetHashMarkCount (11);
	m_slider->SetKeyIncrementValue (2000);
	m_slider->SetLimitLabels (STR_EVENT_QUEUE_LIMIT_LOW, STR_EVENT_QUEUE_LIMIT_HIGH);

	m_popupmenu = (BPopUpMenu *) new BPopUpMenu ("category list");
	BMessage * msg (new BMessage (MSG_CATEGORY_CHANGED));
	msg->AddInt32 ("Category", CC_APPLICATION);
	m_popupmenu->AddItem (new BMenuItem ("Application", msg));
	msg = new BMessage (MSG_CATEGORY_CHANGED);
	msg->AddInt32 ("Category", CC_GENERAL);
	BMenuItem * mi (new BMenuItem ("General", msg));
	//BitmapMenuItem * mi (new BitmapMenuItem (NULL, "General", msg));
	mi->SetMarked (true);
	m_popupmenu->AddItem (mi);
	msg = new BMessage (MSG_CATEGORY_CHANGED);
	msg->AddInt32 ("Category", CC_INTERFACE);
	m_popupmenu->AddItem (new BMenuItem ("Interface", msg));
	msg = new BMessage (MSG_CATEGORY_CHANGED);
	msg->AddInt32 ("Category", CC_KEYBOARD);
	m_popupmenu->AddItem (new BMenuItem ("Keyboard", msg));
	msg = new BMessage (MSG_CATEGORY_CHANGED);
	msg->AddInt32 ("Category", CC_MEDIA);
	m_popupmenu->AddItem (new BMenuItem ("Media", msg));
	msg = new BMessage (MSG_CATEGORY_CHANGED);
	msg->AddInt32 ("Category", CC_MOUSE);
	m_popupmenu->AddItem (new BMenuItem ("Mouse", msg));
	msg = new BMessage (MSG_CATEGORY_CHANGED);
	msg->AddInt32 ("Category", CC_NETWORK);
	m_popupmenu->AddItem (new BMenuItem ("Network", msg));
	msg = new BMessage (MSG_CATEGORY_CHANGED);
	msg->AddInt32 ("Category", CC_PRINTING);
	m_popupmenu->AddItem (new BMenuItem ("Printing", msg));
	msg = new BMessage (MSG_CATEGORY_CHANGED);
	msg->AddInt32 ("Category", CC_STORAGE);
	m_popupmenu->AddItem (new BMenuItem ("Storage", msg));
	msg = new BMessage (MSG_CATEGORY_CHANGED);
	msg->AddInt32 ("Category", CC_SUPPORT);
	m_popupmenu->AddItem (new BMenuItem ("Support", msg));

	m_popupmenu->AddSeparatorItem ();

	msg = new BMessage (MSG_MENU_SEL_ALL_CAT_ALL_EVT);
	m_popupmenu->AddItem (new BMenuItem (STR_SEL_ALL_CAT_ALL_EVT, msg));
	msg = new BMessage (MSG_MENU_USEL_ALL_CAT_ALL_EVT);
	m_popupmenu->AddItem (new BMenuItem (STR_USEL_ALL_CAT_ALL_EVT, msg));

	m_popupmenu->AddSeparatorItem ();

	msg = new BMessage (MSG_MENU_SEL_CUR_CAT_ALL_EVT);
	m_popupmenu->AddItem (new BMenuItem (STR_SEL_CUR_CAT_ALL_EVT, msg));
	msg = new BMessage (MSG_MENU_USEL_CUR_CAT_ALL_EVT);
	m_popupmenu->AddItem (new BMenuItem (STR_USEL_CUR_CAT_ALL_EVT, msg));

	float width1 (StringWidth (STR_CATEGORIES));
	BRect rc;
	rc.left = 5.0f;
	rc.top = m_slider->Frame().bottom + 7.0f;
	rc.right = rc.left + width1 + StringWidth ("Application") + 24.0;
	m_menufld = (BMenuField *) new BMenuField (rc, STR_CATEGORIES, STR_CATEGORIES, m_popupmenu);
	m_menufld->SetDivider (width1);

	BFont font;
	GetFont (&font);

	rc.left = 7.0f;
	rc.right = frame.right - 7.0f - B_V_SCROLL_BAR_WIDTH;
	rc.bottom = rc.top - 5.0f - B_H_SCROLL_BAR_HEIGHT;
	//can't position top yet as the BMenuField doesn't get sized until Attached is called on it.
	//so we must defer sizing of the CLV until AllAttached is called!
	rc.top = m_slider->Frame().bottom + 7.0f;
	m_ColumnListView = new ColumnListView (rc, CLR_FASHIONABLE, &m_bsv, "ClueItemsList", B_FOLLOW_ALL_SIDES,
		B_WILL_DRAW | B_FRAME_EVENTS | B_NAVIGABLE, B_SINGLE_SELECTION_LIST, true, true, true, B_FANCY_BORDER);
	m_ColumnListView->AddColumn (new CLVColumn (STR_TEAM_PROPERTY_COLUMN_VIEW, 20.0f, 0.0f));
	m_ColumnListView->AddColumn (new CLVColumn (STR_TEAM_PROPERTY_COLUMN_EVENT, 20.0f, 0.0f));
	m_ColumnListView->AddColumn (new CLVColumn (STR_TEAM_PROPERTY_COLUMN_DESCRIPTION, font.StringWidth (STR_CT_METHOD_ENTER_DESCRIPTION) + 6.0f, 0.0f));
	m_ColumnListView->AddColumn (new CLVColumn (STR_TEAM_PROPERTY_COLUMN_VALUE, font.StringWidth ("CT_AUDIT_SUCCESS_INDEX") + 6.0f, 0.0f));
	m_ColumnListView->SetInvocationMessage (new BMessage (MSG_LIST_ITEM_INVOCATED));

	m_ColumnListView->AddItem (new PropertyItem (CT_CLASS_BIRTH_INDEX));
	m_ColumnListView->AddItem (new PropertyItem (CT_CLASS_DEATH_INDEX));
	m_ColumnListView->AddItem (new PropertyItem (CT_METHOD_ENTER_INDEX));
	m_ColumnListView->AddItem (new PropertyItem (CT_METHOD_EXIT_INDEX));
	m_ColumnListView->AddItem (new PropertyItem (CT_OK_INDEX));
	m_ColumnListView->AddItem (new PropertyItem (CT_INFO_INDEX));
	m_ColumnListView->AddItem (new PropertyItem (CT_WARNING_INDEX));
	m_ColumnListView->AddItem (new PropertyItem (CT_ERROR_INDEX));
	m_ColumnListView->AddItem (new PropertyItem (CT_AUDIT_SUCCESS_INDEX));
	m_ColumnListView->AddItem (new PropertyItem (CT_AUDIT_FAILURE_INDEX));
	m_ColumnListView->AddItem (new PropertyItem (CT_TIMER_INDEX));
	m_ColumnListView->AddItem (new PropertyItem (CT_OBJECT_INDEX));

	//put in tab order
	AddChild (m_slider);
	AddChild (m_menufld);
	AddChild (m_bsv);

	m_slider->MakeFocus ();
//	RefreshList ();
}


/***************************************************************
***************************************************************/
EditTeamView :: ~EditTeamView
	(
	void
	)
{
	int32			index (m_ColumnListView->CountItems ());
	PropertyItem *	pi (NULL);

	while (index--)
	{
		pi = (PropertyItem *) m_ColumnListView->RemoveItem (index);
		delete pi;
	}
}


/***************************************************************
***************************************************************/
void
EditTeamView :: MessageReceived
	(
	BMessage * msg
	)
{
	switch (msg->what)
	{
		case B_OBSERVER_NOTICE_CHANGE:
			{
			uint32 change (0);
			msg->FindInt32(B_OBSERVE_WHAT_CHANGE, (int32 *) &change);
			switch (change)
			{
			case MSG_SETTINGS_CHANGED:
				{
					SetViewColor (CLR_BACKGROUND);
					SetLowColor (CLR_BACKGROUND);
					Invalidate ();
				}
				break;
			}
			}
			break;
		default:
			BView::MessageReceived (msg);
	}
}


/***************************************************************
***************************************************************/
void
EditTeamView :: AllAttached (void)
{
	EditView::AllAttached ();
//	BMessage msg ('colr');
//	MessageReceived (&msg);
	BWindow * pwnd (Window ());
	if (pwnd)
	{
		((BHandler *)pwnd)->StartWatching ((BHandler *) this, MSG_SETTINGS_CHANGED);
	}
}


/******************************************************************************************************
*******************************************************************************************************/
void
EditTeamView :: AttachedToWindow
	(
	void
	)
{
	EditView::AttachedToWindow ();
}


/******************************************************************************************************
*******************************************************************************************************/
void
EditTeamView :: DetachedFromWindow
	(
	void
	)
{
	EditView::DetachedFromWindow ();
	BWindow * pwnd (Window ());
	if (pwnd)
	{
		((BHandler *)pwnd)->StopWatching ((BHandler *) this, MSG_SETTINGS_CHANGED);
	}
}


/******************************************************************************************************
*******************************************************************************************************/
void
EditTeamView :: Draw
	(
	BRect updateRect
	)
{
	EditView::Draw (updateRect);
}


/***************************************************************
***************************************************************/
bool
EditTeamView :: Save
	(
	void
	)
{
	PRINT (("EditColorView::Save\n"));
	m_Message->MakeEmpty ();
	m_Message->AddData ("Mask", B_RAW_TYPE, &(m_CategoryMask), sizeof(int32) * 10);
	m_Message->AddInt32 ("QueueLength", m_QueueLength);
	return true;
}


/***************************************************************
***************************************************************/
bool
EditTeamView :: PopulateData
	(
	BMessage * message
	)
{
	bool retval (true);
	ssize_t numBytes (0);

	PRINT (("\n\nEditTeamView :: PopulateData\n"));

	status_t sc (B_ERROR);

	void * vptr (NULL);
	sc = message->FindData ("Mask", B_RAW_TYPE, (const void **) &vptr, &numBytes);
	if (sc == B_OK)
	{
		memcpy (&(m_CategoryMask), vptr, numBytes);
		for (int i (0); i < 10; i++)
		{
			PRINT (("%i - 0x%x\n", i, m_CategoryMask[i]));
		}
	}
	else
	{
		PRINT (("Value was not found\n"));
		retval = false;
	}

	sc = message->FindInt32 ("QueueLength", (int32 *) &(m_QueueLength));
	if (sc != B_OK)
	{
		PRINT (("Value was not found\n"));
		retval = false;
	}

	if (retval)
	{
		m_slider->SetValue (m_QueueLength);
	}

	return retval;
}


/***************************************************************
***************************************************************/
EditTeamView *
EditTeamView :: Create
	(
	BRect frame
,	BMessage * message
	)
{
	EditTeamView * pObject (new EditTeamView (frame, message));

	if (pObject)
	{
		if (false == pObject->PopulateData (message))
		{
			delete pObject;
			pObject = NULL;
		}
	}

	return pObject;
}


