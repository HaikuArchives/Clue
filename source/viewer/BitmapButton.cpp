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
#include <InterfaceDefs.h>
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

#ifndef _VIEW_H
#include <View.h>
#endif

#ifndef _BITMAPBUTTON_H
#include "BitmapButton.h"
#endif

#ifndef MAINWINDOW_H
#include "MainWindow.h"
#endif

#ifndef STATUSBARVIEW_H
#include "StatusBarView.h"
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif


/***************************************************************
***************************************************************/
BitmapButton :: BitmapButton
	(
	BPoint pt
,	const BBitmap * bmp
,	BMessage * msg
,	const char * sbar_message
,	const char * tooltip_message
	)
:	BControl (BRect (pt.x, pt.y, pt.x + 23.0, pt.y + 26.0), "bmpbutton", "", msg, B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE)
,	m_bmp (bmp)
,	m_sbar_message (sbar_message)
,	m_tooltip_message (tooltip_message)
{
}


/***************************************************************
***************************************************************/
void
BitmapButton :: MouseDown
	(
	BPoint point
	)
{
	PRINT (("MouseDown: Begin\n"));
	if (IsEnabled ())
	{
		BMessage * curmsg (Window()->CurrentMessage ());
		int32 mousebtn (B_PRIMARY_MOUSE_BUTTON);
		int32 tmp (0);
		curmsg->FindInt32 ("buttons", &mousebtn);
		BMessage * msg (Message ());

		if (B_OK == msg->FindInt32 ("buttons", &tmp))
		{
			msg->ReplaceInt32 ("buttons", mousebtn);
		}
		else
		{
			msg->AddInt32 ("buttons", mousebtn);
		}
		
		if (Value ())
		{
			PRINT (("MouseDown: call Invoke\n"));
			Invoke ();
			SetValue (B_CONTROL_OFF);
			PRINT (("MouseDown: set value = 0\n"));
		}
		else
		{
			PRINT (("MouseDown: call Invoke\n"));
			Invoke ();
			SetValue (B_CONTROL_ON);
			PRINT (("MouseDown: set value = 1\n"));
		}
	}
	PRINT (("MouseDown: End - Value = %i\n", Value ()));
}


/***************************************************************
***************************************************************/
void
BitmapButton :: MouseMoved
	(
	BPoint point
,	uint32 transit
,	const BMessage * message
	)
{
	if (B_ENTERED_VIEW == transit)
	{
		MainWindow * wnd ((MainWindow *) Window ());
		StatusBarView * sbar (wnd->GetStatusBar ());
		if (sbar)
		{
			sbar->SetPaneText (m_sbar_message);
		}

		BMessage postmsg (MSG_TOOL_TIP_START);

		postmsg.AddPoint ("start", ConvertToScreen (point));
		postmsg.AddRect ("bounds", ConvertToScreen (Bounds ()));
		postmsg.AddString ("string", m_tooltip_message);
		be_app->PostMessage (&postmsg);
	}
	else if (B_EXITED_VIEW == transit)
	{
		BMessage postmsg (MSG_TOOL_TIP_STOP);
		be_app->PostMessage (&postmsg);
	}
}


/***************************************************************
***************************************************************/
void
BitmapButton :: KeyDown
	(
	const char * bytes
,	int32 numBytes
	)
{
	PRINT (("KeyDown: Begin\n"));
	switch (bytes[0])
	{
		case B_ENTER:
		case B_SPACE:
			if (Value ())
			{
				PRINT (("KeyDown: call Invoke\n"));
				Invoke ();
				SetValue (B_CONTROL_OFF);
				PRINT (("KeyDown: set value = 0\n"));
			}
			else
			{
				PRINT (("KeyDown: call Invoke\n"));
				Invoke ();
				SetValue (B_CONTROL_ON);
				PRINT (("KeyDown: set value = 1\n"));
			}
			break;
		default:
			BControl::KeyDown (bytes, numBytes);
			break;
	}
	PRINT (("KeyDown: End - Value = %i\n", Value ()));
}


/***************************************************************
***************************************************************/
void
BitmapButton :: Draw
	(
	BRect updateRect
	)
{
	PRINT (("Draw: value = %i\n", Value ()));
	rgb_color navigationColor = keyboard_navigation_color ();
	float offset (Value() ? 1.0 : 0.0);
	DrawButtonFrame ();

	if (IsEnabled ())
	{
		SetDrawingMode (B_OP_OVER);
		SetHighColor (0, 0, 0, 255);
	}
	else
	{
		SetDrawingMode (B_OP_ALPHA);//B_OP_OVER);
		SetBlendingMode(B_CONSTANT_ALPHA, B_ALPHA_OVERLAY);
		SetHighColor (0, 0, 0, 90);
	}

	DrawBitmap (m_bmp, BRect (4.0 + offset, 4.0 + offset, 19.0 + offset, 19.0 + offset));
	SetDrawingMode (B_OP_OVER);
	SetHighColor (0, 0, 0, 255);

	PRINT (("updateRect = %0.f, %0.f, %0.f, %0.f.\n", updateRect.left,updateRect.top,updateRect.right,updateRect.bottom));
	if (IsFocusChanging ())
	{
		PRINT ((" Focus is changing.\n"));
	}
	else
		PRINT ((" Focus is NOT changing.\n"));
	if (IsFocus ())
	{
		PRINT ((" has focus\n"));
		if (Window()->IsActive ())
		{
			PRINT ((" Window is active\n"));
			SetHighColor (keyboard_navigation_color ());
			StrokeLine (BPoint (4.0, 22.0), BPoint (19.0, 22.0));
		}
		else
		{
			PRINT ((" Window is NOT ACTIVE.\n"));
		}
	}
	else
	{
		PRINT ((" NO FOCUS\n"));
	}
}


/***************************************************************
***************************************************************/
void
BitmapButton :: SetEnabled
	(
	bool enabled
	)
{
	BControl::SetEnabled (enabled);
	if (IsFocus ())
	{
		BView * parent (Parent ());
		if (parent)
		{
			parent->MakeFocus (true);
		}
	}
}


/***************************************************************
***************************************************************/
void
BitmapButton :: DrawButtonFrame
	(
	void
	)
{
	BRect drawRect (Bounds());
	BPoint pt1;
	BPoint pt2;
	rgb_color topShadow;
	rgb_color bottomShadow;
	rgb_color filler;
	rgb_color border;
	bool isdown (Value ());

	if (IsEnabled ())
	{
		border = CLR_BLACK;
	}
	else
	{
		border = CLR_TOOLBAR_GREY;
	}

	filler = ui_color (B_MENU_BACKGROUND_COLOR);
	if (isdown)
	{
		filler = tint_color (filler, B_DARKEN_2_TINT);
		topShadow = tint_color (filler, B_DARKEN_3_TINT);
		bottomShadow = tint_color (filler, B_LIGHTEN_2_TINT);
	}
	else
	{
		topShadow = tint_color (filler, B_LIGHTEN_2_TINT);
		bottomShadow = tint_color (filler, B_DARKEN_2_TINT);
	}

	

	// stroke outline
	BeginLineArray (Value () ? 6 : 8);
	pt1.Set (drawRect.left, drawRect.top + 1);
	pt2.Set (drawRect.left, drawRect.bottom - 1);
	AddLine (pt1, pt2, border);
	pt1.Set (drawRect.left + 1, drawRect.top);
	pt2.Set (drawRect.right - 1, drawRect.top);
	AddLine (pt1, pt2, border);
	pt1.Set (drawRect.right, drawRect.top + 1);
	pt2.Set (drawRect.right, drawRect.bottom - 1);
	AddLine (pt1, pt2, border);
	pt1.Set (drawRect.left + 1, drawRect.bottom);
	pt2.Set (drawRect.right - 1, drawRect.bottom);
	AddLine (pt1, pt2, border);
	
	// stroke shadow
	if (isdown)
	{
		drawRect.left += 1.0;
		drawRect.top += 1.0;
	}
	else
	{
		drawRect.InsetBy (1, 1);
	}
	pt1.Set (drawRect.left, drawRect.top);
	pt2.Set (drawRect.left, drawRect.bottom - 1.0);
	AddLine (pt1, pt2, topShadow);
	pt1.Set (drawRect.left + 1.0, drawRect.top);
	pt2.Set (drawRect.right - 1.0, drawRect.top);
	AddLine (pt1, pt2, topShadow);
	if (!isdown)
	{
		pt1.Set (drawRect.right, drawRect.top);
		pt2.Set (drawRect.right, drawRect.bottom);
		AddLine (pt1, pt2, bottomShadow);
		pt1.Set (drawRect.left, drawRect.bottom);
		pt2.Set (drawRect.right - 1, drawRect.bottom);
		AddLine (pt1, pt2, bottomShadow);
	}
	EndLineArray ();

	SetHighColor (filler);
	drawRect.InsetBy (1.0, 1.0);
	FillRect (drawRect);
}
