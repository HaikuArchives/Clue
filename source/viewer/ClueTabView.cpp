//#define DEBUG 1

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

#ifndef _CLUE_TAB_VIEW_H
#include "ClueTabView.h"
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif


/***************************************************************
***************************************************************/
ClueTabView :: ClueTabView
	(
	BRect frame
,	const char * name
,	button_width width 
,	uint32 resizingMode
,	uint32 flags
	)
: 	BTabView (frame, name, width, resizingMode, flags)
{
	SetViewColor (CLR_BACKGROUND);
	SetFlags (Flags () & ~B_NAVIGABLE);
}


/***************************************************************
***************************************************************/
ClueTabView :: ~ClueTabView
	(
	)
{
}


/***************************************************************
***************************************************************/
void
ClueTabView :: Draw
	(
	BRect rc
	)
{
	
	DrawBox (DrawTabs ());
}


/***************************************************************
***************************************************************/
BTab *
ClueTabView :: RemoveTab
	(
	int32 tabIndex
	)
{
	Invalidate ();
	BTab * pRemovedTab (BTabView::RemoveTab (tabIndex));
	if (0 >= CountTabs ())
	{
		SetFlags (Flags () & ~B_NAVIGABLE);
		PRINT (("Change ClueTabView to not be NAVIGABLE\n"));
	}
	else
		PRINT (("ClueTabView is still NAVIGABLE\n"));
	return (pRemovedTab);
}


/***************************************************************
***************************************************************/
void
ClueTabView :: AddTab
	(
	BView * tabContents
,	BTab * tab
	)
{
	BTabView::AddTab (tabContents, tab);
	if (1 == CountTabs ())
	{
		SetFlags (Flags () | B_NAVIGABLE);
	}
}


/***************************************************************
***************************************************************/
void
ClueTabView :: MessageReceived
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
						SetViewColor (CLR_BACKGROUND);
						SetLowColor (CLR_BACKGROUND);
						Invalidate ();
						break;
					default:
						break;
				}
			}
			break;
		default:
			BTabView::MessageReceived (msg);
	}
}


/***************************************************************
***************************************************************/
void
ClueTabView :: AllAttached
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


/***************************************************************
***************************************************************/
BRect
ClueTabView :: DrawTabs
	(
	)
{
//	return BRect (0,0,50,50);
	return BTabView::DrawTabs ();
}


/***************************************************************
***************************************************************/
void
ClueTabView :: DrawBox
	(
	BRect rc
	)
{
//	BTabView::DrawBox (rc);
//	return;
	BView * pview (FindView ("view container"));
	if (pview)
	{
		BRect contrc (pview->Frame ());
		contrc.InsetBy (-1.0f, -1.0f);
		
		SetHighColor (CLR_FOREGROUND_DARK);
		StrokeLine (BPoint (contrc.right, contrc.top), BPoint (contrc.right, contrc.bottom));
		StrokeLine (BPoint (contrc.left, contrc.bottom));

		SetHighColor (CLR_FOREGROUND_LITE);
		StrokeLine (BPoint (contrc.left, contrc.top));
		if (rc.left > 0)
		{
			StrokeLine (BPoint (rc.left - 2.0f, contrc.top));
			StrokeLine (BPoint (rc.right + 3.0f, contrc.top), BPoint (contrc.right, contrc.top));
		}
		else
		{
			StrokeLine (BPoint (contrc.right, contrc.top));
		}
	}
}


/***************************************************************
***************************************************************/
void
ClueTabView :: Select
	(
	int32 tab
	)
{
	bool resetfocus (false);
	const char * pChar (NULL);

	//Since the BView will be detached from the window, we must disable its focus
	//before it's detached.
	BTab * pCurTab (TabAt (Selection ()));

	if (NULL != pCurTab) //there may be no tabs in the BTabView, so check first!
	{
		BView * pFocusView (Window()->CurrentFocus ());
		if (NULL != pFocusView)
		{
			pChar = pFocusView->Name ();
			BView * pView (pCurTab->View ());
			if (NULL != pView)
			{
				BView * pChildView (pView->FindView (pChar));
				if (NULL != pChildView)
				{
					if (pChildView->IsFocus ())
					{
						pChildView->MakeFocus (false);
						resetfocus = true;
						PRINT (("resetfocus now true\n"));
					}
				}
			}
		}
	}

	BTabView::Select (tab);

	//To be nice, we'll reset the focus if we lost it above.
	if (resetfocus)
	{
		pCurTab = TabAt (tab);
		BView * pView (pCurTab->View ());
		if (NULL != pView)
		{
			BView * pChildView (pView->FindView (pChar));
			if (NULL != pChildView)
			{
				pChildView->MakeFocus (true);
			}
		}
	}
}


/***************************************************************
***************************************************************/
void
ClueTabView :: SetFocusTab
	(
	int32 tab
,	bool focused
	)
{
//	PRINT (("SetFocusTab\n"));
//	if (false == focused)
//	{
//		BRect rc (TabFrame (tab));
//		Invalidate (Bounds ());
//		Window()->UpdateIfNeeded ();
//	}
	BTabView::SetFocusTab (tab, focused);
}

