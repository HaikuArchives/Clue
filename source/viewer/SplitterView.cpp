/*	
	2000 Jeff Braun
	web: www.citylinq.com/brauns
	email1: yobkadon@hotmail.com
	email2: brauns@citylinq.com
*/

/***************************************************************
include header files
***************************************************************/
//#define DEBUG 1

#ifndef _APPLICATION_H
#include <Application.h>
#endif

#ifndef _CURSOR_H
#include <Cursor.h>
#endif

#ifndef _DEBUG_H
#include <Debug.h>
#endif

#ifndef _MESSAGE_H
#include <Message.h>
#endif

#ifndef _POINT_H
#include <Point.h>
#endif

#ifndef _RECT_H
#include <Rect.h>
#endif

#ifndef _WINDOW_H
#include <Window.h>
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif

#ifndef SPLITTERVIEW_H
#include "SplitterView.h"
#endif

static const unsigned char kCursorEastWest[] =
{
	16,1,2,2,
	//pixel color data
	0,0,
	0,0,
	56,0,
	36,0,
	36,0,
	19,224,
	18,92,
	9,42,
	8,1,
	60,1,
	76,73,
	66,133,
	49,255,
	12,133,
	2,72,
	1,0,
	//now comes the mask
	0,0,
	0,0,
	56,0,
	60,0,
	60,0,
	31,224,
	31,252,
	15,254,
	15,255,
	63,255,
	127,255,
	127,255,
	63,255,
	15,255,
	3,254,
	1,248
};


/***************************************************************
***************************************************************/
SplitterView :: SplitterView
	(
	BRect frame
,	char * name
,	uint32 resizingMode
,	uint32 flags
	)
:	BView (frame, name, B_FOLLOW_TOP_BOTTOM, flags | B_WILL_DRAW)
//:	BView (frame, name, B_FOLLOW_TOP_BOTTOM, flags)// | B_WILL_DRAW)
,	m_tracking (false)
,	inview (false)
{
//	BCursor pCursor ((BCursor *) new BCursor (kCursorEastWest));
	SetViewColor (CLR_BACKGROUND);
//	SetViewColor (B_TRANSPARENT_COLOR);
}


/***************************************************************
***************************************************************/
/*
void
SplitterView :: AllAttached
	(
	void
	)
{
	SetViewCursor ((BCursor *) new BCursor ((const void *) kCursorEastWest));
}
*/


/***************************************************************
***************************************************************/
void
SplitterView :: Draw
	(
	BRect updateRect
	)
{
	PRINT (("Splitter :: Draw\n"));
	//BView::Draw (updateRect);
	//if (inview)
	//	SetHighColor (255, 0, 0, 255);
	//else
//	SetHighColor (CLR_BACKGROUND);
//	FillRect (updateRect);
	BRect rc (Bounds ());
//	StrokeLine (BPoint (rc.left, updateRect.top), BPoint (rc.left, updateRect.bottom));
//	StrokeLine (BPoint (rc.right, updateRect.top), BPoint (rc.right, updateRect.bottom));

	uint32 rows (1 + ((int) rc.Height () / 3));
	PRINT (("view height=%f\n", rc.Height ()));
	PRINT (("rows= %i\n", rows));

//	BPoint start (0.0f, 0.0f);
//	BPoint end (0.0f, 0.0f);
	BPoint pt (0.0f, 0.0f);
	BPoint pt2 (0.0f, 0.0f);

	BeginLineArray (rows * 2);
	pt.x = 0.0f;
	pt2.x = 1.0f;

	for (uint32 i (0); i < rows; ++i)
	{
		PRINT (("printing row %i\n", i));
		pt.y = i * 3;
		pt2.y = pt.y + 1;
		AddLine (pt, pt, CLR_BACKGROUND_DARK);
		AddLine (pt2, pt2, CLR_BACKGROUND_LITE);
	}
	EndLineArray ();

	BeginLineArray (rows * 2);
	pt.x = 3.0f;
	pt2.x = 4.0f;

	for (uint32 i (0); i < rows; ++i)
	{
		PRINT (("printing row %i\n", i));
		pt.y = i * 3;
		pt2.y = pt.y + 1;
		AddLine (pt, pt, CLR_BACKGROUND_DARK);
		AddLine (pt2, pt2, CLR_BACKGROUND_LITE);
	}
	EndLineArray ();
}


/***************************************************************
***************************************************************/
void
SplitterView :: MessageReceived
	(
	BMessage * message
	)
{
	uint32 buttons (0);
	BPoint cursor;

	switch (message->what)
	{
		case MSG_SPLITTER_STOP:
			PRINT (("MSG_SPLITTER_STOP\n"));
			m_tracking = false;
			GetMouse (&cursor, &buttons, false);
			//it's possible that the mouse has left the view but we haven't been told to 
			if (!Bounds().Contains (cursor))
			{
				inview = false;
//				SetViewColor (180, 180, 180, 255);
//				Invalidate ();
				PRINT (("Splitter setting Cursor to B_HAND_CURSOR\n"));
				be_app->SetCursor (B_HAND_CURSOR);
			}
			break;
		case B_OBSERVER_NOTICE_CHANGE:
			{
			uint32 change (0);
			message->FindInt32(B_OBSERVE_WHAT_CHANGE, (int32 *) &change);
			switch (change)
			{
			case MSG_SETTINGS_CHANGED:
				{
					SetViewColor (CLR_BACKGROUND);
					Invalidate ();
				}
				break;
			}
			}
			break;
		default:
			BView::MessageReceived (message);
			break;
	}
}



/***************************************************************
***************************************************************/
void
SplitterView :: MouseDown
	(
	BPoint point
	)
{
	PRINT (("MouseDown\n"));
	BMessage msg (MSG_SPLITTER_START);
	//Window()->PostMessage (&msg, Parent ());
	Parent()->MessageReceived (&msg);
	m_tracking = true;
	if (!inview)
	{
		inview = true;
//		SetViewColor (255, 0, 0, 255);
//		Invalidate ();
	}
}


/***************************************************************
***************************************************************/
void
SplitterView :: MouseMoved
	(
	BPoint point
,	uint32 transit
,	const BMessage * message
	)
{
	if (!m_tracking)
	{
		BMessage * msg (Window()->CurrentMessage ());
		int32 buttons (0);
		msg->FindInt32 ("buttons", &buttons);
		if (buttons) return;

		if (B_ENTERED_VIEW == transit)
		{
//			uint32 buttons (0);
//			BPoint cursor;
//			GetMouse (&cursor, &buttons, false);
//			if (!buttons) //if no buttons are pressed!
//			{
				inview = true;
//				SetViewColor (255, 0, 0, 255);
//				Invalidate ();
				PRINT (("Splitter setting Cursor2\n"));
				be_app->SetCursor (kCursorEastWest);
//			}
		}
		else if (B_EXITED_VIEW == transit)
		{
			inview = false;
//			SetViewColor (180, 180, 180, 255);
//			Invalidate ();
			PRINT (("Splitter setting Cursor3\n"));
			be_app->SetCursor (B_HAND_CURSOR);
		}
	}
	else if (B_EXITED_VIEW == transit) //we're tracking! check to see if still valid
	{
		uint32 buttons;
		BPoint cursor;
		GetMouse (&cursor, &buttons, false);
		//it's possible that the mouse has left the view but we haven't been told to 
		if (!buttons) //if no buttons are pressed!
		{
			PRINT (("Alternative MSG_SPLITTING_STOP\n"));
			inview = false;
//			SetViewColor (180, 180, 180, 255);
//			Invalidate ();
			m_tracking = false;
			PRINT (("Splitter setting Cursor4\n"));
			be_app->SetCursor (B_HAND_CURSOR);
		}
	}
}


/***************************************************************
***************************************************************/
void
SplitterView :: MouseUp
	(
	BPoint point
	)
{
	PRINT (("CSplitterView :: MouseUp\n"));
	if (!m_tracking)
	{
		PRINT (("not currently tracking\n"));
		uint32 buttons;
		BPoint cursor;
		GetMouse (&cursor, &buttons, false);
		if (Bounds().Contains (cursor))
		{
			PRINT (("was in bounds, so highlight!\n"));
			inview = true;
//			SetViewColor (255, 0, 0, 255);
//			Invalidate ();
			PRINT (("Splitter setting Cursor5\n"));
			be_app->SetCursor (kCursorEastWest);
		}
	}
}


/***************************************************************
***************************************************************/
void
SplitterView :: AttachedToWindow
	(
	void
	)
{
	BWindow * pwnd (Window ());
	if (pwnd)
	{
		((BHandler *)pwnd)->StartWatching ((BHandler *) this, MSG_SETTINGS_CHANGED);
	}
}


