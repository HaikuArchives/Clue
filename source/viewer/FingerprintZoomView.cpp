//#define DEBUG 1

#ifndef _ALERT_H
#include <Alert.h>
#endif

#ifndef __BSTRING__
#include <String.h>
#endif

#ifndef _MESSENGER_H
#include <Messenger.h>
#endif

#ifndef _APP_FILE_INFO_H
#include <AppFileInfo.h>
#endif

#ifndef _APPLICATION_H
#include <Application.h>
#endif

#ifndef _TEXT_CONTROL_H
#include "TextControl.h"
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

#ifndef _FILE_H
#include <File.h>
#endif

#ifndef _FONT_H
#include <Font.h>
#endif

#ifndef _MENU_ITEM_H
#include <MenuItem.h>
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

#ifndef _POP_UP_MENU_H
#include <PopUpMenu.h>
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

#ifndef _SCROLL_BAR_H
#include <ScrollBar.h>
#endif

#ifndef _SCROLL_VIEW_H
#include <ScrollView.h>
#endif

#ifndef __BSTRING__
#include <String.h>
#endif

#ifndef _TEXTVIEW_H
#include <TextView.h>
#endif

#ifndef _TIME_H_
#include <time.h>
#endif

#ifndef _VIEW_H
#include <View.h>
#endif

#ifndef _WINDOW_H
#include <Window.h>
#endif

#ifndef CLUE_H
#define CLUE
#define BUILD_CLUE_APPLICATION
#include "Clue.h"
#endif

#ifndef _FINGERPRINTZOOMVIEW_H
#include "FingerprintZoomView.h"
#endif

#ifndef _CLUEITEM_H_
#include "ClueItem.h"
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif

#include <Beep.h>

class MyTextView : public BTextView
{
	public:
		MyTextView (BRect frame, const char * name, BRect textRect, uint32 resizeMask, uint32 flags = B_WILL_DRAW | B_PULSE_NEEDED)
		:	BTextView (frame, name, textRect, resizeMask, flags)
		,	m_Scroller (NULL)
		{
		}
		virtual void MakeFocus (bool focusState = true)
		{
			if (m_Scroller)
			{
				m_Scroller->SetBorderHighlighted (focusState);
			}
			BTextView::MakeFocus (focusState);
		}
		virtual void TargetedByScrollView (BScrollView *scroller)
		{
			m_Scroller = scroller;
			BView::TargetedByScrollView (scroller);
		}
		virtual void AttachedToWindow (void)
		{
			BView::AttachedToWindow ();
			//need to do the following because of draw bug:
			//if the scrollbar is > 0, the text is not scrolled in the TextView correctly.
			//instead, it's set at 0.  This fixes that problem until Be fixes the BTextView
			if (m_Scroller)
			{
				BScrollBar * pSB (m_Scroller->ScrollBar (B_VERTICAL));
				if (NULL != pSB)
				{
					float val (pSB->Value ());
					if (val > 0)
					{
						pSB->SetValue (val - 1);
						pSB->SetValue (val);
					}
				}
			}
		}
	private:
		BScrollView *	m_Scroller;
};



FingerprintZoomView :: FingerprintZoomView
	(
	BRect frame
,	ClueItem * pClueItem
	)
:	BView (frame, "Fingerprint Zoom View", B_FOLLOW_ALL_SIDES, B_WILL_DRAW | B_PULSE_NEEDED)
,	m_CAT (pClueItem->m_CAT)
,	m_EVT (pClueItem->m_EVT)
,	m_Time (pClueItem->m_Time)
,	m_ThreadID (pClueItem->m_ThreadID)
,	m_TeamID (pClueItem->m_TeamID)
,	m_Line (pClueItem->m_Line)
,	m_Sequence (pClueItem->m_Sequence)
,	m_File (pClueItem->m_File)
,	m_Method (pClueItem->m_Method)
,	m_Class (pClueItem->m_Class)
,	m_Description (pClueItem->m_Description)
,	m_Detail (pClueItem->m_Detail)
,	m_IsDown (true)
,	m_TextView (NULL)
,	m_ScrollView (NULL)
,	m_Button (NULL)
,	m_TextControl (NULL)
,	m_maxW (0.0f)
,	m_fontheight (0.0f)
{
	SetViewColor (CLR_BACKGROUND);
	
	BRect trect (0.0f, 0.0f, 0.0f, 0.0f);
	BRect TVFrame (0.0f, frame.bottom - 200.0f, frame.right - B_V_SCROLL_BAR_WIDTH, frame.bottom - B_H_SCROLL_BAR_HEIGHT); 

	m_TextView = new MyTextView (TVFrame, "ZoomDetailView", trect, B_FOLLOW_ALL_SIDES, B_WILL_DRAW | B_NAVIGABLE);
	m_TextView->SetStylable (false);
	m_TextView->MakeEditable (false);
	m_TextView->SetWordWrap (false);
	m_TextView->SetFontAndColor (be_fixed_font);
	m_TextView->SetText (pClueItem->m_Detail);
//	AddChild (pTextView);
//							BRect trect (0,0,0,0); 
	m_ScrollView = new BScrollView("ZoomDetailScrollView", m_TextView, B_FOLLOW_ALL_SIDES, 0, true, true);
//	BScrollView * pBSV (new BScrollView("ZoomDetailScrollView", pTextView, B_FOLLOW_LEFT_RIGHT | B_FOLLOW_BOTTOM, 0, true, true));
	AddChild (m_ScrollView);
/*
	frame.bottom -= 60.0f;
	frame.right -= B_V_SCROLL_BAR_WIDTH;
	m_outline = new BOutlineListView (frame, "objectfilter_list", B_SINGLE_SELECTION_LIST, B_FOLLOW_ALL_SIDES);
	CreateList (m_outline);

	m_outline->SetSelectionMessage (new BMessage ('msel'));
	m_outline->SetInvocationMessage (new BMessage ('invo'));
	AddChild (new BScrollView ("scroll_objectfilter_items", m_outline, B_FOLLOW_ALL_SIDES, 0, false, true));

	frame.left = 15.0f;
	frame.top = frame.bottom + 15.0f;
//	frame.right = 50;
//	frame.bottom = 180;
	m_btnClose = static_cast<BButton *>(new BButton (frame, "Close", "Close", new BMessage (MSG_OK), B_FOLLOW_LEFT | B_FOLLOW_BOTTOM));
	m_btnClose->MakeDefault (true);
	AddChild (m_btnClose);

	m_btnEnableAll = static_cast<BButton *>(new BButton (frame, "Enable All Subitems", "Enable All Subitems", new BMessage ('enab'), B_FOLLOW_LEFT | B_FOLLOW_BOTTOM));
	m_btnEnableAll->SetEnabled (false);
	AddChild (m_btnEnableAll);

	m_btnDisableAll = static_cast<BButton *>(new BButton (frame, "Disable All Subitems", "Disable All Subitems", new BMessage ('disa'), B_FOLLOW_LEFT | B_FOLLOW_BOTTOM));
	m_btnDisableAll->SetEnabled (false);
	AddChild (m_btnDisableAll);
*/
//	frame.top
//	m_TextControl = static_cast<BTextControl *>(new BTextControl (BRect (5.0f, 5.0f, frame.right, 10.0f), "Detail", "Detail", pClueItem->m_Detail, NULL));
//	AddChild (m_TextControl);

	BRect rc (frame.left, frame.bottom - 205.0f, frame.right, 10.0f);
	m_Button = static_cast<BButton *>(new BButton (rc, "Slide", "--------", new BMessage ('slid'), B_FOLLOW_LEFT_RIGHT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE | B_FULL_UPDATE_ON_RESIZE));
	AddChild (m_Button);
}


FingerprintZoomView :: ~FingerprintZoomView
	(
	void
	)
{
}


/***************************************************************
***************************************************************/
void
FingerprintZoomView :: MessageReceived
	(
	BMessage * msg
	)
{
	//put in most-frequent to less-frequent order for that little extra speed we all want!
	switch (msg->what)
	{
		case 'slid':
			{
			BWindow *pWnd (Window ());
			if (pWnd)
			{
				pWnd->SetPulseRate (100000);
//			beep ();
			}
			}
			break;
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
FingerprintZoomView :: AllAttached
	(
	void
	)
{
	BRect trect (0.0f, 0.0f, 0.0f, 0.0f);
							int n = m_TextView->CountLines ();
							float filewidth (1.0f);
							float t (0.0f);

							for (int i (0); i < n; i++)
							{
								t = m_TextView->LineWidth (i);
								if (t > filewidth)
								{
									filewidth = t;
								}
							}

							trect.right = filewidth;
							m_TextView->SetTextRect (trect);
	
	BFont font;
	GetFont (&font);
	font.SetFace (B_BOLD_FACE);
	SetFont (&font, B_FONT_FACE);
	GetFont (&font);
	float f (font.StringWidth (m_File.String ()));
	m_maxW = f;

	f = font.StringWidth (STR_ZOOM_CATEGORY);
	if (f > m_maxW)
		m_maxW = f;
	
	f = font.StringWidth (STR_ZOOM_EVENT);
	if (f > m_maxW)
		m_maxW = f;
	
	f = font.StringWidth (STR_ZOOM_DATETIME);
	if (f > m_maxW)
		m_maxW = f;
	
	f = font.StringWidth (STR_ZOOM_THREADID);
	if (f > m_maxW)
		m_maxW = f;
	
	f = font.StringWidth (STR_ZOOM_TEAMID);
	if (f > m_maxW)
		m_maxW = f;
	
	f = font.StringWidth (STR_ZOOM_LINE);
	if (f > m_maxW)
		m_maxW = f;
	
	f = font.StringWidth (STR_ZOOM_SEQUENCE);
	if (f > m_maxW)
		m_maxW = f;
	
	f = font.StringWidth (STR_ZOOM_FILE);
	if (f > m_maxW)
		m_maxW = f;
	
	f = font.StringWidth (STR_ZOOM_METHOD);
	if (f > m_maxW)
		m_maxW = f;
	
	f = font.StringWidth (STR_ZOOM_CLASS);
	if (f > m_maxW)
		m_maxW = f;
	
	f = font.StringWidth (STR_ZOOM_DESCRIPTION);
	if (f > m_maxW)
		m_maxW = f;

	m_maxW += 10.0f;
	
	font_height fh;
	font.GetHeight (&fh);
	m_fontheight = fh.ascent + fh.descent + fh.leading;

	BRect bnds (Bounds ());
	int Y (m_fontheight);
	m_ScrollView->MoveTo (-2.0f, 14.0f * Y);
	m_ScrollView->ResizeTo (bnds.right + 4.0f, bnds.bottom - (14.0f * Y) + 2.0f);

	m_Button->MoveTo (2.0f, 13.0f * Y);
	m_Button->SetTarget (this);
	m_Button->ResizeTo (bnds.right - 4.0f, Y);
	m_Button->MakeFocus (true);
}


void
FingerprintZoomView :: Draw
	(
	BRect rect
	)
{
	SetDrawingMode (B_OP_OVER);

	BFont font;
	GetFont (&font);
	font.SetFace (B_REGULAR_FACE);
	font.SetFace (B_BOLD_FACE);
	//font.SetSize (14.0f);
	SetFont (&font, B_FONT_ALL);

	DrawString (STR_ZOOM_CATEGORY, BPoint (4.0f, m_fontheight * 2));
	DrawString (STR_ZOOM_EVENT, BPoint (4.0f, m_fontheight * 3));
	DrawString (STR_ZOOM_DATETIME, BPoint (4.0f, m_fontheight * 4));
	DrawString (STR_ZOOM_THREADID, BPoint (4.0f, m_fontheight * 5));
	DrawString (STR_ZOOM_TEAMID, BPoint (4.0f, m_fontheight * 6));
	DrawString (STR_ZOOM_LINE, BPoint (4.0f, m_fontheight * 7));
	DrawString (STR_ZOOM_SEQUENCE, BPoint (4.0f, m_fontheight * 8));
	DrawString (STR_ZOOM_FILE, BPoint (4.0f, m_fontheight * 9));
	DrawString (STR_ZOOM_METHOD, BPoint (4.0f, m_fontheight * 10));
	DrawString (STR_ZOOM_CLASS, BPoint (4.0f, m_fontheight * 11));
	DrawString (STR_ZOOM_DESCRIPTION, BPoint (4.0f, m_fontheight * 12));

	GetFont (&font);
	font.SetFace (B_REGULAR_FACE);
//	font.SetSize (12.0f);
	SetFont (&font, B_FONT_ALL);

	const char * pChar (NULL);
	switch (m_CAT)
	{
		case CC_GENERAL:
			pChar = "CC_GENERAL";
			break;
		case CC_APPLICATION:
			pChar = "CC_APPLICATION";
			break;
		case CC_INTERFACE:
			pChar = "CC_INTERFACE";
			break;
		case CC_MEDIA:
			pChar = "CC_MEDIA";
			break;
		case CC_STORAGE:
			pChar = "CC_STORAGE";
			break;
		case CC_SUPPORT:
			pChar = "CC_SUPPORT";
			break;
		case CC_NETWORK:
			pChar = "CC_NETWORK";
			break;
		case CC_MOUSE:
			pChar = "CC_MOUSE";
			break;
		case CC_KEYBOARD:
			pChar = "CC_KEYBOARD";
			break;
		case CC_PRINTING:
			pChar = "CC_PRINTING";
			break;
		default:
			pChar = "<error>";
			break;
	}
	DrawString (pChar, BPoint (m_maxW, m_fontheight * 2));
	
	switch (m_EVT)
	{
		case CE_OK:
			pChar = "CE_OK";
			break;
		case CE_INFO:
			pChar = "CE_INFO";
			break;
		case CE_WARNING:
			pChar = "CE_WARNING";
			break;
		case CE_ERROR:
			pChar = "CE_ERROR";
			break;
		case CE_SUCCEEDED:
			pChar = "CE_SUCCEEDED";
			break;
		case CE_FAILED:
			pChar = "CE_FAILED";
			break;
		case CE_ENTER:
			pChar = "CE_ENTER";
			break;
		case CE_EXIT:
			pChar = "CE_EXIT";
			break;
		case CE_TIMER:
			pChar = "CE_TIMER";
			break;
		case CE_BIRTH:
			pChar = "CE_BIRTH";
			break;
		case CE_DEATH:
			pChar = "CE_DEATH";
			break;
		case CE_OBJECT:
			pChar = "CE_OBJECT";
			break;
		default:
			pChar = "<error>";
			break;
	}
	DrawString (pChar, BPoint (m_maxW, m_fontheight * 3));

	char tmpstr[30];
	char tmpstr2[30];
	time_t mytime (m_Time / 1000000);
	struct tm * pTime (localtime (&mytime));
	strftime (tmpstr, 30, "%d/%m/%Y", pTime);

//			time_t mytime (m_Time / 1000000);
//			struct tm * pTime (localtime (&mytime));
	mytime = m_Time - (mytime * 1000000);
	sprintf (tmpstr, "%s, %02i:%02i:%02i.%06li", tmpstr, pTime->tm_hour, pTime->tm_min, pTime->tm_sec, mytime);

	DrawString (tmpstr, BPoint (m_maxW, m_fontheight * 4));

	BString str;
	str << m_ThreadID;
	DrawString (str.String (), BPoint (m_maxW, m_fontheight * 5));

	str.SetTo (NULL);
	str << m_TeamID;
	DrawString (str.String (), BPoint (m_maxW, m_fontheight * 6));

	str.SetTo (NULL);
	str << m_Line;
	DrawString (str.String (), BPoint (m_maxW, m_fontheight * 7));

	str.SetTo (NULL);
	str << m_Sequence;
	DrawString (str.String (), BPoint (m_maxW, m_fontheight * 8));

	DrawString (m_File.String (), BPoint (m_maxW, m_fontheight * 9));
	DrawString (m_Method.String (), BPoint (m_maxW, m_fontheight * 10));
	DrawString (m_Class.String (), BPoint (m_maxW, m_fontheight * 11));
	DrawString (m_Description.String (), BPoint (m_maxW, m_fontheight * 12));
}


void
FingerprintZoomView :: MouseDown
	(
	BPoint point
	)
{
	BPopUpMenu * pPopupmenu ((BPopUpMenu *) new BPopUpMenu ("TeamSelect"));

	BMenuItem * pBMI (new BMenuItem (STR_CLOSE_ALL_OPEN_ZOOM_WINDOWS, new BMessage (MSG_CLOSE_ALL_ZOOM_WINDOWS)));
	pBMI->SetTarget (be_app);
	pPopupmenu->AddItem (pBMI);

	ConvertToScreen (&point);
	pPopupmenu->Go (point, true, false, true);
}


void
FingerprintZoomView :: Pulse
	(
	void
	)
{
	if (m_IsDown)
	{
		PRINT (("move up, "));
		BRect bnds (m_ScrollView->Frame ());
		int amt (20);
		int fh (m_fontheight);
		int top (bnds.top);
		if ((top - 20) > (fh - 1))
		{
			amt = 20;
			PRINT ((" set it to 20; "));
		}
		else
		{
			PRINT (("  disable pulse  "));
			Window()->SetPulseRate (0);
			m_IsDown = false;
			amt = top - (fh - 1);
		}
		PRINT (("amt=%i; curtop=%i, fh=%i\n", amt, top, fh));

		m_Button->MoveBy (0.0f, -amt);
		m_ScrollView->MoveBy (0.0f, -amt);
		m_ScrollView->ResizeBy (0.0f, amt);
	}
	else
	{
		PRINT (("move down; "));
		BRect bnds (m_ScrollView->Frame ());
		int amt (20);
		int top (bnds.top);
		int fh (m_fontheight);
		if ((top + amt) < (14 * fh))
		{
			PRINT ((" set it to 20; "));
			amt = 20;
		}
		else //if ((top + amt) > (14 * fh))
		{
			PRINT (("  disable pulse; "));
			Window()->SetPulseRate (0);
			m_IsDown = true;
			amt = (top + 20) - (14 * fh);
		}
		PRINT (("amt=%i; top=%i, fh=%i\n", amt, top, fh));
				
		m_Button->MoveBy (0.0f, amt);
		m_ScrollView->MoveBy (0.0f, amt);
		m_ScrollView->ResizeBy (0.0f, -amt);
	}
}



